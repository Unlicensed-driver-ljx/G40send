#include "g400camera.h"
#include "../Camera/xdma.h"

G400Camera::G400Camera()
{
    m_img_width = g_param->displayParam.VS_size.width;
    m_img_height = g_param->displayParam.VS_size.height;
// 初始化各种图像缓冲区
//    m_mono16 = Mat::zeros(g_param->Height,g_param->Width,CV_16UC1);
//    m_mono16_bkd = Mat::zeros(g_param->Height,g_param->Width,CV_16UC1);
//    m_mono16_scale = Mat::zeros(m_img_height,m_img_width,CV_16UC1);
    m_mono8 = Mat::zeros(m_img_height,m_img_width,CV_8UC1);
//    m_mono16_bin = Mat::zeros(g_param->Height/2,g_param->Width/2,CV_16UC1);
//    m_mono8_jd = Mat::zeros(m_img_height,m_img_width,CV_8UC1);
//    m_mono16bkd = Mat::zeros(g_param->Height,g_param->Width,CV_16UC1);
//    m_mono16bkd1 = Mat::zeros(g_param->Height,g_param->Width,CV_16UC1);
//    m_mono16bkd2 = Mat::zeros(g_param->Height,g_param->Width,CV_16UC1);
    getFiberTestImage();
//    cv::imshow("",g_param->fiberTestImage);
}

G400Camera::~G400Camera()
{
    f_threadUartRecvA = false;
    f_threadUartSendA = false;
    f_threadUartRecvB = false;
    f_threadUartSendB = false;
    close();
}

bool G400Camera::init()
{
    _width = g_param->cameraconfigParam.ResolutionW;
    _height = g_param->cameraconfigParam.ResolutionH;
    g_param->Width = g_param->cameraconfigParam.ResolutionW;
    g_param->Height = g_param->cameraconfigParam.ResolutionH;
    uint32_t taps = g_param->cameraconfigParam.ImageTap;
    uint32_t bits = g_param->cameraconfigParam.ImageBit;
    uint32_t mode;
    qDebug()<<"_width"<<_width<<"_height"<<_height<<"taps"<<taps<<"bits"<<bits;
    switch (g_param->cameraconfigParam.CameraLinkMode)
    {
    case 0:
        mode = 0x0;
        break;
    case 1:
        mode = 0x1;
        break;
    case 2:
        mode = 0x2;
        break;
    default:
        break;
    }
    uint32_t num = 4;
    _bytes_per_pixel = (bits == 8 ? 1 : 2);
    _bytes_per_tap = (taps == 3 ? 3 : 1);
   // camera_cam_size = _width*_height*_bytes_per_pixel*taps;
  //  camera_cam_size = _width*_height*_bytes_per_pixel*_bytes_per_tap;
    camera_cam_size = _width*_height*_bytes_per_pixel*_bytes_per_tap;
    GetCameraParam(_width, _height, taps, bits, mode, num);

    return true;
}

void G400Camera::close()
{
    stopCapture();
    closecameralink_recv();
    xdma_app_receive_stop();
}

void G400Camera::stopsend()
{
    xdma_send_stop();
    xdma_app_uart_recv_stop();
    xdma_app_send_stop();
}

void G400Camera::startCapture()
{
    g_param->imageDisplay = NULL;

    xdma_receive_proc();
    m16count = _width*_height;
    
    // 初始化串口 - 设置串口0和全局配置的串口
    uart_port_init(0,g_param->controlParam.TestCameraBaud);
    uart_port_init(g_param->controlParam.qSerialPort.toInt(),115200);
    g_param->uart_recv_work = true;

    // 初始化串口A并启动串口接收线程
    uart_port_init(UART_PORT_A, 115200);  // 初始化串口A，波特率115200
    f_threadUartRecvA = true;  // 设置接收线程运行标志
    pthread_create(&pthreadUartRecvA, nullptr, WrapperUartRecvA, this);  // 创建接收线程
    uart_port_init(UART_PORT_B, 115200);  // 初始化串口A，波特率115200
    f_threadUartRecvB = true;  // 设置接收线程运行标志
    pthread_create(&pthreadUartRecvB, nullptr, WrapperUartRecvB, this);  // 创建接收线程


    // 启动串口发送线程
    f_threadUartSendA = true;  // 设置发送线程运行标志
    pthread_create(&pthreadUartSendA, nullptr, WrapperUartSendA, this);  // 创建发送线程

    f_threadUartSendB = true;  // 设置发送线程运行标志
    pthread_create(&pthreadUartSendB, nullptr, WrapperUartSendB, this);  // 创建发送线程

    if(m_bCapture == false)
    {
        m_bCapture = true;
        start(QThread::NormalPriority);
    }
}

void G400Camera::stopCapture()
{
    m_bCapture = false;
}

bool G400Camera::readCurrentFrame()
{
    if(outputImageState() == rev_ImageState)
    {
        return false;
    }
    rev_ImageState = outputImageState();
    _buf = outputMat();
    if(_buf == NULL)
    {
        qDebug() << "G400Camrea::readCurrentFrame mono16_raw NULL";
        return false;
    }
    if(g_param->Width == 0 || g_param->Height == 0)
    {
        return false;
    }
    bufToRGB();

    //cv::resize(curMat, curMat_scale, Size(m_img_width, m_img_height));

    return true;
}

void G400Camera::starReceive()
{
    for(int i=0;i<30;i++){
        uchar* t = new uchar[75497472];
        rev_List.append(t);
    }
}

void G400Camera::stopReceive()
{
    char file_name[32];
    for(int i=0;i<30;i++){
        uchar* t = rev_List[i];
        sprintf(file_name, "cameralink_recv_%d.bin", i);
        /* write file */
        write_file(file_name, t, 75497422);
    }
}

void G400Camera::run()
{
    bRefreshTime = true;
    while(true == m_bCapture )
    {
        qDebug() << "Camera::run --------";
      //  usleep(1000000);
        if(bRefreshTime == true)
        {
            time_fps_counter = cv::getTickCount();
        }
        if(readCurrentFrame() == true)
        {
            g_param->EstimateGather = true;
            bRefreshTime = true;
            if(curMat_scale.empty() || curMat_scale.cols <= 0 || curMat_scale.rows <= 0)
            {
                qDebug() << "Camera::run curMat_scale size error";
                continue;
            }

            g_param->show = g_param->controlParam.ShowImage;
            if(g_param->cameraconfigParam.ImageBit > 8)
            {
//                contrastStretch(g_param->displayParam.IR_up_factor, g_param->displayParam.IR_low_factor);
//                if(m_mono8.empty())
//                {
//                    qDebug() << "InfraredCamera::run m_mono8 size error";
//                    continue;
//                }
//                cv::cvtColor(m_mono8, m_rgb8, COLOR_GRAY2RGB);
                g_param->imageProcessQueue_VS.enqueue(curMat_scale);
                curMat_scale.copyTo(g_param->imageDisplay);
            }
            else
            {
      //          if(g_param->cameraconfigParam.ImageTap == 1)
      //          {
      //              cv::cvtColor(curMat_scale, m_rgb8, COLOR_GRAY2RGB);
      //              m_rgb8.copyTo(g_param->imageDisplay);
      //              g_param->imageProcessQueue_VS.enqueue(m_rgb8);
      //          }
      //          else
      //          {
                    curMat_scale.copyTo(g_param->imageDisplay);
                    g_param->imageProcessQueue_VS.enqueue(curMat_scale);
      //          }

            }

        }
        else
        {
            bRefreshTime = false;
            continue;
        }
        time_fps_counter = cv::getTickCount() - time_fps_counter;
        totalFramefps = (cv::getTickFrequency() / time_fps_counter);
        g_param->camerafps = totalFramefps;

    }
}

bool G400Camera::contrastStretch(float up_factor, float low_factor)
{
    Mat means, stddevs;
    double upper_bound;
    double lower_bound;
    meanStdDev(curMat_scale, means, stddevs);
    upper_bound = means.at<double>(0) + up_factor*stddevs.at<double>(0);
    lower_bound = means.at<double>(0) - low_factor*stddevs.at<double>(0);

    if(upper_bound <= lower_bound)
    {
        double tmp = upper_bound;
        lower_bound = upper_bound;
        upper_bound = tmp;
    }
    if(lower_bound < 0)
    {
        lower_bound = 0;
    }
    if(upper_bound > 65535)
    {
        upper_bound = 65535;
    }
    for(int j = 0; j < m_img_height; j++)
    {
        for(int i = 0; i < m_img_width; i++)
        {
            if(curMat_scale.at<ushort>(j,i) < lower_bound)
            {
                m_mono8.at<uchar>(j,i) = 0;
            }
            else if(curMat_scale.at<ushort>(j,i) > upper_bound)
            {
                m_mono8.at<uchar>(j,i) = 255;
            }
            else
            {
                m_mono8.at<uchar>(j,i) = (uchar)((curMat_scale.at<ushort>(j,i) - lower_bound) * 255.0 / (upper_bound - lower_bound + 0.0000001));
            }
        }
    }
    return true;

}

void G400Camera::bufToRGB()
{
    if(g_param->cameraconfigParam.ImageBit > 8)
    {
        cv::Mat ImageMat(g_param->cameraconfigParam.ResolutionH,g_param->cameraconfigParam.ResolutionW,CV_16UC1,_buf);
        cv::resize(ImageMat,curMat,cv::Size(1024,1024));
        curMat.convertTo(curMat_scale,CV_8UC1);
    }
    else
    {
   //     if(g_param->cameraconfigParam.ImageTap == 1 )
   //     {
   //         cv::Mat ImageMat(g_param->cameraconfigParam.ResolutionH,g_param->cameraconfigParam.ResolutionW,CV_8UC1,_buf);
   //         ImageMat.copyTo(curMat);
   //         if(g_param->controlParam.TCPOPEN == true)
   //         {
   //             memcpy(g_param->framebuffer,curMat.data,1920*1080);
   //             emit SignalGrabData();
   //         }

   //     }
        if(g_param->cameraconfigParam.ImageTap == 1 || g_param->cameraconfigParam.ImageTap == 2)
   //     if(g_param->cameraconfigParam.ImageTap == 2)
        {
  //          cv::Mat ImageMat(g_param->cameraconfigParam.ResolutionH,g_param->cameraconfigParam.ResolutionW,CV_8UC2,_buf);
            cv::Mat ImageMat(g_param->cameraconfigParam.ResolutionH,g_param->cameraconfigParam.ResolutionW,CV_8UC1,_buf);
            ImageMat.copyTo(curMat);
        }
        else if(g_param->cameraconfigParam.ImageTap == 3)
        {
            cv::Mat ImageMat(g_param->cameraconfigParam.ResolutionH,g_param->cameraconfigParam.ResolutionW,CV_8UC3,_buf);
//            curMat.reserveBuffer(g_param->cameraconfigParam.ResolutionH * g_param->cameraconfigParam.ResolutionW * 3);
            ImageMat.copyTo(curMat);
//            if(g_param->controlParam.TCPOPEN == true)
//            {
//                memcpy(g_param->framebuffer,curMat.data,640*512);
//                emit SignalGrabData();
//            }
        }
    }
}

void G400Camera::getFiberTestImage()
{
    // 1. 读取原始彩色图像
    cv::Mat src = cv::imread("../CAMERACONTROL/OR4040FSI.png", cv::IMREAD_GRAYSCALE/*IMREAD_UNCHANGED*/); // 读取为8 bit彩色图像
    if (src.empty()) {
        std::cerr << "Error: Unable to open input image!" << std::endl;
        return ;
    }

//    if(src.channels()==4){
//        cv::cvtColor(src,src,cv::COLOR_BGR2BGRA);
//    }
//    cv::imshow("1024*1024",src);
//    cv::waitKey(0);
    // 2. 调整图像分辨率
    cv::Mat resized;
    cv::resize(src, resized, cv::Size(4096, 4096), 0, 0, cv::INTER_LINEAR/*INTER_LANCZOS4*/); // 放大到6144×6144

//    cv::imshow("6144*6144",resized);
//    cv::waitKey(0);

    // 3. 转换为16 bit
    cv::Mat dst;
//    resized.convertTo(dst, CV_16UC3); // 转换为16 bit无符号整数
    resized.convertTo(dst, CV_16UC1); // 转换为16 bit无符号整数

//    // 4. 确保fiberTestImage地址固定
//    if (g_param->fiberTestImage.empty()) {
//        // 首次初始化：创建固定大小的图像
//        g_param->fiberTestImage.create(4096, 4096, CV_16UC1);
//        qDebug() << "fiberTestImage initialized with fixed address:" << (void*)g_param->fiberTestImage.data;
//    }
    
//    // 检查目标图像尺寸和类型是否匹配
//    if (g_param->fiberTestImage.rows == dst.rows &&
//        g_param->fiberTestImage.cols == dst.cols &&
//        g_param->fiberTestImage.type() == dst.type()) {
//        // 直接拷贝数据到固定地址，不改变fiberTestImage的地址
        dst.copyTo(g_param->fiberTestImage);
//        qDebug() << "Data copied to fixed fiberTestImage address:" << (void*)g_param->fiberTestImage.data;
//    } else {
//        qDebug() << "Error: Size or type mismatch in fiberTestImage!";
//        qDebug() << "Expected:" << g_param->fiberTestImage.rows << "x" << g_param->fiberTestImage.cols
//                 << "Type:" << g_param->fiberTestImage.type();
//        qDebug() << "Got:" << dst.rows << "x" << dst.cols << "Type:" << dst.type();
//    }

//    cv::Mat showimg;
//    dst.convertTo(showimg,CV_8UC1/*,255.0/65535.0,0*/);
//    cv::imshow("6144*6144 16bit",showimg);
//    cv::waitKey(0);
//    cv::destroyAllWindows();
}


/**
 * 从指定串口读取数据
 * @param port 串口端口号
 * @param buff 接收数据的缓冲区
 * @return 成功读取的字节数，无数据则返回0
 */
unsigned int G400Camera::read_uart(unsigned char port, char *buff)
{
    // 获取串口FIFO缓冲区中可读的数据量
    uint32_t count1 = getlen_fifo(port);

    if (count1 > 0)  // 如果有数据可读
    {
        if (count1 >= 1024) // 防止缓冲区溢出
        {
            count1 = 1024;
        }
        
        // 调用底层uart_read函数读取数据
        int val1 = uart_read(port, buff, count1);
        
        return val1;  // 返回实际读取的字节数
    }
    else
    {
        return 0;  // 无数据可读，返回0
    }
}

void G400Camera::portRecv()
{

    int portNum = 0;
    // qDebug()<<"bhyssss";

    uint32_t count1 = getlen_fifo(portNum);
    if (count1 > 0) qDebug() << count1;
    if (count1 >= 64)
    {
        //  ui->plainTextEdit->clear();
        char buf1[64] = {0};

        qDebug() << "xxx";
        int val1 = uart_read(portNum, buf1, count1);
        int val2 = uart_read(portNum, buf1, count1);
        int val3 = uart_read(portNum, buf1, count1);
        int val4 = uart_read(portNum, buf1, count1);
        int val5 = uart_read(portNum, buf1, count1);
        int val6 = uart_read(portNum, buf1, count1);
        qDebug() << "sss" << val2 << val3 << val4 << val5 << val6;
        // usleep(100);
        for (int i = 0; i < 64; i++)
        {
            qDebug() << "ttt";
            //  ui->plainTextEdit->insertPlainText(QString::number(buf1[i])+","+QString::number(val1)+"\r\n");
        }
    }
}

/**
 * 串口AB接收处理函数 - 在单独线程中运行
 * 持续监听并处理串口A接收到的数据
 */
void G400Camera::UartRecvProcessA(){
    qDebug() << "Received from port A";
    while(f_threadUartRecvA){  // 线程运行标志为true时持续运行
        QThread::usleep(200);  // 休眠200微秒，避免CPU占用过高
        int iport = UART_PORT_A;  // 指定串口A
        int iNumber;
        char t_ucpReceiveCode[1024];  // 接收数据的缓冲区
        
        // 尝试读取串口数据
        iNumber = read_uart(iport, t_ucpReceiveCode);
        if (iNumber <= 0) continue;  // 如果没有读到数据，继续下一轮循环
        
        // 在这里处理收到的串口数据，数据buf为t_ucpReceiveCode，数据数量为iNumber
        qDebug() << "Received from port " << iport << "len " << iNumber;
        // 实际应用中应根据协议解析并处理接收到的数据
    }
}

void G400Camera::UartRecvProcessB(){
    qDebug() << "Received from port B";
    while(f_threadUartRecvB){  // 线程运行标志为true时持续运行
        QThread::usleep(200);  // 休眠200微秒，避免CPU占用过高
        int iport = UART_PORT_B;  // 指定串口A
        int iNumber;
        char t_ucpReceiveCode[1024];  // 接收数据的缓冲区

        // 尝试读取串口数据
        iNumber = read_uart(iport, t_ucpReceiveCode);
        if (iNumber <= 0) continue;  // 如果没有读到数据，继续下一轮循环

        // 在这里处理收到的串口数据，数据buf为t_ucpReceiveCode，数据数量为iNumber
        qDebug() << "Received from port " << iport << "len " << iNumber;
        // 实际应用中应根据协议解析并处理接收到的数据
    }
}
/**
 * 向指定串口发送数据
 * @param port 串口端口号
 * @param data 要发送的数据
 * @param len 要发送的数据长度
 */
void G400Camera::sendToUart(unsigned char port, const char *data, unsigned int len) {
    if (data == nullptr || len == 0) {
        qDebug() << "No data to send or length is zero";
        return;
    }
    
    // 将 const char* 转换为 char*（去掉 const 限定符）
    // 这是因为底层uart_write函数需要非const指针参数
    char *nonConstData = const_cast<char*>(data);
    
    // 调用底层的 uart_write 函数，进行类型转换以匹配函数签名
    // uart_write函数原型：int uart_write(uint32_t uart_num, char *buf, uint32_t count)
    int sentBytes = uart_write(static_cast<uint32_t>(port), nonConstData, static_cast<uint32_t>(len));
    
    // 处理发送结果
    if (sentBytes < 0) {
        qDebug() << "Failed to send data";
    } else {
        //qDebug() << "sucess to send data";
       // qDebug() << "Sent" << sentBytes << "bytes to port" << port;

    }
}

/**
 * 串口AB发送处理函数 - 在单独线程中运行
 * 持续向串口A发送数据
 */

void G400Camera::UartSendAProcess(){
    qDebug() << "Sending to port A";
    while(f_threadUartSendA){  // 线程运行标志为true时持续运行
        QThread::usleep(200);  // 休眠200微秒，控制发送频率

        // 要发送的数据，这里是一个固定的字符串
        // 在实际应用中，应根据需要构建要发送的数据包
        const char *message = "Hello UART1-ljx";

        // 发送数据到串口A
        sendToUart(UART_PORT_A, message, strlen(message));
        // 每200微秒发送一次数据
    }
}
void G400Camera::UartSendBProcess(){
    qDebug() << "Sending to port B";
    while(f_threadUartSendB){  // 线程运行标志为true时持续运行
        QThread::usleep(200);  // 休眠200微秒，控制发送频率

        // 要发送的数据，这里是一个固定的字符串
        // 在实际应用中，应根据需要构建要发送的数据包
        const char *message = "Hello UART2-ljx";

        // 发送数据到串口A
        sendToUart(UART_PORT_B, message, strlen(message));
        // 每200微秒发送一次数据
    }
}

// 接收线程包装函数
/**
 * 接收线程的包装函数 - 用于pthread_create创建线程
 * @param arg 线程参数，实际上是G400Camera对象指针
 */
void *WrapperUartRecvA(void *arg){
    G400Camera *NowQTracker = (G400Camera *)(arg);  // 将参数转换为G400Camera对象指针
    NowQTracker->UartRecvProcessA();  // 调用对象的接收处理方法
}

void *WrapperUartRecvB(void *arg){
    G400Camera *NowQTracker = (G400Camera *)(arg);  // 将参数转换为G400Camera对象指针
    NowQTracker->UartRecvProcessB();  // 调用对象的接收处理方法
}
// 发送线程包装函数
/**
 * 发送线程的包装函数 - 用于pthread_create创建线程
 * @param arg 线程参数，实际上是G400Camera对象指针
 */
void *WrapperUartSendA(void *arg){
    G400Camera *NowQTracker = (G400Camera *)(arg);  // 将参数转换为G400Camera对象指针
    NowQTracker->UartSendAProcess();  // 调用对象的发送处理方法
}
void *WrapperUartSendB(void *arg){
    G400Camera *NowQTracker = (G400Camera *)(arg);  // 将参数转换为G400Camera对象指针
    NowQTracker->UartSendBProcess();  // 调用对象的发送处理方法
}
