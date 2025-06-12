#include "g400camera.h"

G400Camera::G400Camera()
{
    m_img_width = g_param->displayParam.VS_size.width;
    m_img_height = g_param->displayParam.VS_size.height;

    m_mono16 = Mat::zeros(g400_width,g400_height,CV_16UC1);
    m_mono16_bkd = Mat::zeros(g400_width,g400_height,CV_16UC1);
    m_mono16_scale = Mat::zeros(m_img_height,m_img_width,CV_16UC1);
    m_mono8 = Mat::zeros(m_img_height,m_img_width,CV_8UC1);

    m_buffer_idx = 0;
    m_remove_bkd = false;
    m_store_bkd_once = false;
}

G400Camera::~G400Camera()
{
    close();
}

bool G400Camera::init()
{
    int err;
    m_buffer_idx = 0;
    /// close first
    close();
    /// open
    int ret = pxd_PIXCIopen(DRIVERPARMS, "", FORMATFILE);

    if(ret < 0)
    {
        /// error report
        qDebug() << "pxd_PIXCIopen error: " << ret;
        pxd_mesgFault(UNITSMAP);
        return false;
    }

    qDebug() << "pxd_PIXCIopen success: " << ret;

//    if (pxd_eventCapturedFieldCreate(1, SIGUSR1, NULL) >= 0)
//    {
//        printf("Hooked signal upon captured field");
//    }
    //err = pxd_goLive(UNITSMAP,1);
    err = pxd_goLivePair(UNITSMAP, 1, 2);
    //err = pxd_goLiveSeq(UNITSMAP, 1, pxd_imageZdim(), 1, pxd_imageZdim(), pxd_imageIdim());
    qDebug() << "err" << err;
    pxd_mesgFault(UNITSMAP);

    ///info
    qDebug() << "Image frame buffer memory size: " << pxd_infoMemsize(UNITSMAP)/1024;
    qDebug() << "Image frame buffers           : " << pxd_imageZdim();
    qDebug() << "Number of boards              : " << pxd_infoUnits();

    qDebug() << "Image resolution:";
    qDebug() << "xdim           = " << pxd_imageXdim();
    qDebug() << "ydim           = " << pxd_imageYdim();
    qDebug() << "colors         = " << pxd_imageCdim();
    qDebug() << "bits per pixel = " << pxd_imageCdim()*pxd_imageBdim();

    qDebug() <<"G400 Visual Camera width: "<<pxd_imageXdim() <<", height: " << pxd_imageYdim();

    if (pxd_serialConfigure(UNITSMAP, 0,  9600, 8, 0, 1, 0, 0, 0) < 0)
    {
        qDebug() << "pxd_serialConfigure error";
        return false;
    }

    return true;
}

void G400Camera::close()
{
    stopCapture();
    msleep(10);
    int ret = 0;
    do
    {
        ret = pxd_PIXCIclose();
        qDebug() << "pxd_PIXCIclose" << ret;
        msleep(50);
    }while(ret >= 0);   
}

void G400Camera::startCapture()
{
    setMode(0);
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

void G400Camera::do_videoSeq()
{
      int     err;
      err = pxd_goLiveSeq(UNITSMAP, 1, pxd_imageZdim(), 1, pxd_imageZdim(), pxd_imageIdim());
       //err = pxd_goLivePair(UNITSMAP, 1, 2);
       printf("pxd_goLiveSeq: %s\n", err>=0? "Ok": pxd_mesgErrorCode(err));

       if (err >= 0) {
       struct timeval timeval, timeval2;
       gettimeofday(&timeval, NULL);
       //
       printf("Capturing images ...");
       while (pxd_goneLive(UNITSMAP, 0)) {
           usleep(5000);
           gettimeofday(&timeval2, NULL);
           if (timeval2.tv_sec > timeval.tv_sec+30) {
           pxd_goAbortLive(UNITSMAP);
          // user("Image seqeunce capture aborted after 30 seconds");
           return;
           }
           usleep(5000);
       }

       printf("\n");
       }

       pxd_mesgFault(UNITSMAP);
}

bool G400Camera::readCurrentFrame()
{
//    if (pxd_capturedBuffer(UNITSMAP) == m_buffer_idx)
//    {
//        //qDebug() << "pxd_capturedBuffer = " << pxd_capturedBuffer(UNITSMAP);
//        //qDebug() << "m_buffer_idx = " << m_buffer_idx;
//        //qDebug() << "m_buffer_idx error = " << pxd_capturedBuffer(UNITSMAP);
//        return false;
//    }
    //qDebug() << "pxd_capturedBuffer = " << pxd_capturedBuffer(UNITSMAP);
    //qDebug() << "m_buffer_idx = " << m_buffer_idx;
//    if (!pxd_goneLive(UNITSMAP, 0))
//        {
//            //qDebug() << "pxd_capturedBuffer = " << pxd_capturedBuffer(UNITSMAP);
//            //qDebug() << "m_buffer_idx = " << m_buffer_idx;
//            //qDebug() << "m_buffer_idx error = " << pxd_capturedBuffer(UNITSMAP);
//            return false;
//        }
//    m_buffer_idx = pxd_capturedBuffer(UNITSMAP);

//   qDebug() << "m_buffer_idx = " << m_buffer_idx;

    do_videoSeq();
    char color_space[] = "Grey";
   ushort* mono16_raw = (ushort*)(m_mono16.data);
    if(mono16_raw == NULL)
    {
        qDebug() << "G400Camrea::readCurrentFrame mono16_raw NULL";
        return false;
    }

//    int u;
//    static ushort  monoimage_buf16[9*10];

//    for (u = 0; u < UNITS; u++)
//    {

//      int count = pxd_readushort(1<<u, 1, (pxd_imageXdim()-9)/2, (pxd_imageYdim()-10)/2, (pxd_imageXdim()-9)/2+9, (pxd_imageYdim()-10)/2+10, monoimage_buf16, sizeof(monoimage_buf16)/sizeof(ushort), "Grey");

//    }


    int count = pxd_readushort(UNITSMAP, 1, 0, 0, g400_width, g400_height, mono16_raw, g400_width*g400_height, color_space);
       qDebug()<<QString("pxd_readushort: %1\n").arg(count);
    /*if(count != g400_width*g400_height)
    {
        qDebug() << "G400Camrea::readCurrentFrame() pxd_readushort size error"<<count;
        if (count < 0)
            qDebug()<<QString("pxd_readushort: %1\n").arg(pxd_mesgErrorCode(count));
        return false;
    }*/




    /// sub bkd 20191205

    if(m_store_bkd_once == true)
    {
        m_store_bkd_once = false;
        m_mono16_bkd = m_mono16.clone();
    }

    if(m_remove_bkd == true)
    {
        cv::absdiff(m_mono16, m_mono16_bkd, m_mono16);
    }

    /// resize
    cv::resize(m_mono16, m_mono16_scale, Size(m_img_width, m_img_height));
    return true;
}

bool G400Camera::setMode(int index)
{
       char    databuffer[16];   // buffer large enough for command and response
       unsigned char buff[5];
       unsigned char crc = 0;
       int     r;
       databuffer[0] = 0x7e;
       databuffer[1] = 0x30;
       databuffer[2] = 0x45;
       databuffer[3] = 0x36;
       databuffer[4] = 0x30;
       databuffer[5] = 0x31;
       databuffer[6] = 0x32;
       databuffer[7] = 0x31;
       databuffer[8] = 0x36;

       buff[0] = 0x60;
       buff[1] = 0x12;
       buff[2] = 0x16;

    switch(index)
    {
    case 0: /// HG
        buff[3] = 0x00;
        buff[4] = 0x01;
        break;
    case 1: /// LG
        //buf[3] = 0x01;
        //buf[4] = 0x10;
       // buf[2] = 0x07;
        buff[3] = 0x00;
        buff[4] = 0x02;
        break;
    case 2: /// STD
        buff[3] = 0x00;
        buff[4] = 0x00;
        break;
    default: /// HG
        buff[3] = 0x00;
        buff[4] = 0x01;
        break;
    }
    crc = ((unsigned char)buff[0] + (unsigned char)buff[1]+ (unsigned char)buff[2]+ (unsigned char)buff[3]+ (unsigned char)buff[4])%256;
    databuffer[9] = ((buff[3]&0xf0)>>4) > 0x09 ? ((buff[3]&0xf0)>>4)+ 0x37 : ((buff[3]&0xf0)>>4) + 0x30;
    databuffer[10] = (buff[3]&0x0f) > 0x09 ? (buff[3]&0x0f)+0x37 : (buff[3]&0x0f) + 0x30;
    databuffer[11] = ((buff[4]&0xf0)>>4) > 0x09 ? ((buff[4]&0xf0)>>4)+0x37 : ((buff[4]&0xf0)>>4) + 0x30;
    databuffer[12] = (buff[4]&0x0f) > 0x09 ? (buff[4]&0x0f)+0x37 : (buff[4]&0x0f) + 0x30;
    databuffer[13] = ((crc&0xf0)>>4) > 0x09 ? ((crc&0xf0)>>4)+0x37 : ((crc&0xf0)>>4) + 0x30;
    databuffer[14] = (crc&0x0f) > 0x09 ? (crc&0x0f)+0x37 : (crc&0x0f) + 0x30;
    databuffer[15] = 0x3e;
    r = pxd_serialWrite(UNITSMAP, 0, databuffer, strlen(databuffer));
    if(r < 0)
    {
        qDebug() << "setMode error " << index;
        return false;
    }
    return true;
}

bool G400Camera::setGain(int index)
{
    char    databuffer[16];   // buffer large enough for command and response
       unsigned char buff[5];
       unsigned char crc = 0;
       int     r;
       databuffer[0] = 0x7e;
       databuffer[1] = 0x30;
       databuffer[2] = 0x45;
       databuffer[3] = 0x36;
       databuffer[4] = 0x30;
       databuffer[5] = 0x31;
       databuffer[6] = 0x32;
       databuffer[7] = 0x32;
       databuffer[8] = 0x30;

       buff[0] = 0x60;
       buff[1] = 0x12;
       buff[2] = 0x20;

       switch(index)
       {
       case 0:
           buff[3] = 0x00;
           buff[4] = 0x00;
           break;
       case 1:
           buff[3] = 0x00;
           buff[4] = 0x04;
           break;
       case 2:
           buff[3] = 0x00;
           buff[4] = 0x08;
           break;
       case 3:
           buff[3] = 0x00;
           buff[4] = 0x0c;
           break;
       case 4:
           buff[3] = 0x00;
           buff[4] = 0x10;
           break;
       case 5:
           buff[3] = 0x00;
           buff[4] = 0x14;
           break;
       case 6:
           buff[3] = 0x00;
           buff[4] = 0x18;
           break;
       case 7:
           buff[3] = 0x00;
           buff[4] = 0x1c;
           break;
       case 8:
           buff[3] = 0x00;
           buff[4] = 0x20;
           break;
       case 9:
           buff[3] = 0x00;
           buff[4] = 0x24;
           break;
       case 10:
           buff[3] = 0x00;
           buff[4] = 0x28;
           break;
       case 11:
           buff[3] = 0x00;
           buff[4] = 0x2c;
           break;
       case 12:
           buff[3] = 0x00;
           buff[4] = 0x30;
           break;
       case 13:
           buff[3] = 0x00;
           buff[4] = 0x34;
           break;
       case 14:
           buff[3] = 0x00;
           buff[4] = 0x38;
           break;
       case 15:
           buff[3] = 0x00;
           buff[4] = 0x3c;
           break;
       case 16:
           buff[3] = 0x00;
           buff[4] = 0x3e;
           break;
       default:
           buff[3] = 0x00;
           buff[4] = 0x00;
           break;
       }
        crc = ((unsigned char)buff[0] + (unsigned char)buff[1]+ (unsigned char)buff[2]+ (unsigned char)buff[3]+ (unsigned char)buff[4])%256;
        databuffer[9] = ((buff[3]&0xf0)>>4) > 0x09 ? ((buff[3]&0xf0)>>4)+ 0x37 : ((buff[3]&0xf0)>>4) + 0x30;
        databuffer[10] = (buff[3]&0x0f) > 0x09 ? (buff[3]&0x0f)+0x37 : (buff[3]&0x0f) + 0x30;
        databuffer[11] = ((buff[4]&0xf0)>>4) > 0x09 ? ((buff[4]&0xf0)>>4)+0x37 : ((buff[4]&0xf0)>>4) + 0x30;
        databuffer[12] = (buff[4]&0x0f) > 0x09 ? (buff[4]&0x0f)+0x37 : (buff[4]&0x0f) + 0x30;
        databuffer[13] = ((crc&0xf0)>>4) > 0x09 ? ((crc&0xf0)>>4)+0x37 : ((crc&0xf0)>>4) + 0x30;
        databuffer[14] = (crc&0x0f) > 0x09 ? (crc&0x0f)+0x37 : (crc&0x0f) + 0x30;
        databuffer[15] = 0x3e;
        r = pxd_serialWrite(UNITSMAP, 0, databuffer, strlen(databuffer));
        if (r < 0)
        {
            qDebug()<<"CL LGI Send Error";
            return false;

        }
     return true;
}

bool G400Camera::setExposure(int ms)
{
    char    databuffer[16];   // buffer large enough for command and response
    unsigned char buff[5];
    unsigned char crc = 0;
    int     r;
    unsigned int inte = 0;
    if(ms < 34)
    {
        ms = 34;
    }
    inte = (float)ms/32.25;//32.25
    //inte = ms;
    //send low
    databuffer[0] = 0x7e;
    databuffer[1] = 0x30;
    databuffer[2] = 0x45;
    databuffer[3] = 0x36;
    databuffer[4] = 0x30;
    databuffer[5] = 0x31;
    databuffer[6] = 0x32;
    databuffer[7] = 0x30;
    databuffer[8] = 0x36;

    buff[0] = 0x60;
    buff[1] = 0x12;
    buff[2] = 0x06;
    buff[3] = (unsigned char)((inte&0xff000000)>>24);
    buff[4] = (unsigned char)((inte&0x00ff0000)>>16);


     crc = ((unsigned char)buff[0] + (unsigned char)buff[1]+ (unsigned char)buff[2]+ (unsigned char)buff[3]+ (unsigned char)buff[4])%256;
     databuffer[9] = ((buff[3]&0xf0)>>4) > 0x09 ? ((buff[3]&0xf0)>>4)+ 0x37 : ((buff[3]&0xf0)>>4) + 0x30;
     databuffer[10] = (buff[3]&0x0f) > 0x09 ? (buff[3]&0x0f)+0x37 : (buff[3]&0x0f) + 0x30;
     databuffer[11] = ((buff[4]&0xf0)>>4) > 0x09 ? ((buff[4]&0xf0)>>4)+0x37 : ((buff[4]&0xf0)>>4) + 0x30;
     databuffer[12] = (buff[4]&0x0f) > 0x09 ? (buff[4]&0x0f)+0x37 : (buff[4]&0x0f) + 0x30;
     databuffer[13] = ((crc&0xf0)>>4) > 0x09 ? ((crc&0xf0)>>4)+0x37 : ((crc&0xf0)>>4) + 0x30;
     databuffer[14] = (crc&0x0f) > 0x09 ? (crc&0x0f)+0x37 : (crc&0x0f) + 0x30;
     databuffer[15] = 0x3e;
     r = pxd_serialWrite(UNITSMAP, 0, databuffer, strlen(databuffer));
     if (r < 0)
     {
         qDebug()<<"CL LGI Send Error";
         return false;

     }
     //send high
     databuffer[0] = 0x7e;
     databuffer[1] = 0x30;
     databuffer[2] = 0x45;
     databuffer[3] = 0x36;
     databuffer[4] = 0x30;
     databuffer[5] = 0x31;
     databuffer[6] = 0x32;
     databuffer[7] = 0x30;
     databuffer[8] = 0x35;

     buff[0] = 0x60;
     buff[1] = 0x12;
     buff[2] = 0x05;
     buff[3] = (unsigned char)((inte&0x0000ff00)>>8);
     buff[4] = (unsigned char)((inte&0x000000ff));


      crc = ((unsigned char)buff[0] + (unsigned char)buff[1]+ (unsigned char)buff[2]+ (unsigned char)buff[3]+ (unsigned char)buff[4])%256;
      databuffer[9] = ((buff[3]&0xf0)>>4) > 0x09 ? ((buff[3]&0xf0)>>4)+ 0x37 : ((buff[3]&0xf0)>>4) + 0x30;
      databuffer[10] = (buff[3]&0x0f) > 0x09 ? (buff[3]&0x0f)+0x37 : (buff[3]&0x0f) + 0x30;
      databuffer[11] = ((buff[4]&0xf0)>>4) > 0x09 ? ((buff[4]&0xf0)>>4)+0x37 : ((buff[4]&0xf0)>>4) + 0x30;
      databuffer[12] = (buff[4]&0x0f) > 0x09 ? (buff[4]&0x0f)+0x37 : (buff[4]&0x0f) + 0x30;
      databuffer[13] = ((crc&0xf0)>>4) > 0x09 ? ((crc&0xf0)>>4)+0x37 : ((crc&0xf0)>>4) + 0x30;
      databuffer[14] = (crc&0x0f) > 0x09 ? (crc&0x0f)+0x37 : (crc&0x0f) + 0x30;
      databuffer[15] = 0x3e;
      r = pxd_serialWrite(UNITSMAP, 0, databuffer, strlen(databuffer));
      if (r < 0)
      {
          qDebug()<<"CL LGI Send Error";
          return false;

      }


    qDebug()<<"enter CL expose";

  /*  r = pxd_serialWrite(UNITSMAP, 0, databuffer, strlen(databuffer));
    if (r < 0)
    {
        qDebug()<<"CL LGI Send Error";
        return false;

    }*/
    return true;
}

bool G400Camera::resetCL()
{
    char    databuffer[16];   // buffer large enough for command and response
       unsigned char buff[5];
       unsigned char crc = 0;
       int     r;
       databuffer[0] = 0x7e;
       databuffer[1] = 0x30;
       databuffer[2] = 0x45;
       databuffer[3] = 0x36;
       databuffer[4] = 0x30;
       databuffer[5] = 0x31;
       databuffer[6] = 0x32;
       databuffer[7] = 0x31;
       databuffer[8] = 0x38;

       buff[0] = 0x60;
       buff[1] = 0x12;
       buff[2] = 0x18;


       buff[3] = 0x00;
       buff[4] = 0x20;

        crc = ((unsigned char)buff[0] + (unsigned char)buff[1]+ (unsigned char)buff[2]+ (unsigned char)buff[3]+ (unsigned char)buff[4])%256;
        databuffer[9] = ((buff[3]&0xf0)>>4) > 0x09 ? ((buff[3]&0xf0)>>4)+ 0x37 : ((buff[3]&0xf0)>>4) + 0x30;
        databuffer[10] = (buff[3]&0x0f) > 0x09 ? (buff[3]&0x0f)+0x37 : (buff[3]&0x0f) + 0x30;
        databuffer[11] = ((buff[4]&0xf0)>>4) > 0x09 ? ((buff[4]&0xf0)>>4)+0x37 : ((buff[4]&0xf0)>>4) + 0x30;
        databuffer[12] = (buff[4]&0x0f) > 0x09 ? (buff[4]&0x0f)+0x37 : (buff[4]&0x0f) + 0x30;
        databuffer[13] = ((crc&0xf0)>>4) > 0x09 ? ((crc&0xf0)>>4)+0x37 : ((crc&0xf0)>>4) + 0x30;
        databuffer[14] = (crc&0x0f) > 0x09 ? (crc&0x0f)+0x37 : (crc&0x0f) + 0x30;
        databuffer[15] = 0x3e;
        r = pxd_serialWrite(UNITSMAP, 0, databuffer, strlen(databuffer));
        if (r < 0)
        {
            qDebug()<<"CL LGI Send Error";
            return false;

        }
     return true;
}

void G400Camera::storeBackground()
{
    m_store_bkd_once = true;
}

void G400Camera::removeBackground(bool flag)
{
    m_remove_bkd = flag;
}

void G400Camera::run()
{
    while(true == m_bCapture)
    {
        double time_profile_counter = 0;
       time_profile_counter = cv::getCPUTickCount();

        if(readCurrentFrame() == true)
        {
            if(m_mono16_scale.empty() || m_mono16_scale.cols <= 0 || m_mono16_scale.rows <= 0)
            {
                qDebug() << "InfraredCamera::run m_mono16 size error";
                continue;
            }
            time_profile_counter = cv::getCPUTickCount() - time_profile_counter;
            qDebug() <<"read Time FPS" << 1000 * (cvGetTickFrequency() * 1000) / time_profile_counter;

            if(g_param->debugParam.bSaveRawFileOnceGrab == true)
            {
                QDir dir;
                if(!dir.exists("/home/nvidia/Pictures"))
                {
                    dir.mkdir("/home/nvidia/Pictures");
                }
                QString path = QString("/home/nvidia/Pictures/%1.tif").arg(cv::getCPUTickCount());
               /* if(!dir.exists("/media/nvidia/92EA-1F0F/Pictures"))
                {
                      dir.mkdir("/media/nvidia/92EA-1F0F/Pictures");
                }
                QString path = QString("/media/nvidia/92EA-1F0F/Pictures/%1.tif").arg(cv::getCPUTickCount());*/
                //QString path = QString("/home/nvidia/Pictures/%1.tif").arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss.zzz"));
                cv::imwrite(path.toLatin1().data(), m_mono16);

                qDebug() << "1111 ";
                qDebug() << "save raw image in " << path;
            }


            contrastStretch(g_param->displayParam.IR_up_factor, g_param->displayParam.IR_low_factor);
            if(m_mono8.empty())
            {
                qDebug() << "InfraredCamera::run m_mono8 size error";
                continue;
            }
            //cv::cvtColor(m_mono8, m_rgb8, COLOR_GRAY2RGB);
            Mat bb;
            cv::flip(m_mono8, bb, -1);
            cv::cvtColor(bb, m_rgb8, COLOR_GRAY2BGR);
            if(g_param->displayParam.imgSource == VISUAL)
            {
                //m_rgb8.copyTo(g_param->imageDisplay);
            }
            else
            {
                m_rgb8.copyTo(g_param->imageDisplay_small);
            }

            g_param->imageProcessQueue_VS.enqueue(m_rgb8);

            if(g_param->debugParam.bSaveRawFileOnceGrab == true)
            {
                QDir dir;
                if(!dir.exists("/home/nvidia/Pictures"))
                {
                    dir.mkdir("/home/nvidia/Pictures");
                }
                QString path = QString("/home/nvidia/Pictures/%1.jpg").arg(cv::getCPUTickCount());
               /* if(!dir.exists("/media/nvidia/92EA-1F0F/Pictures"))
                {
                     dir.mkdir("/media/nvidia/92EA-1F0F/Pictures");
                }
                QString path = QString("/media/nvidia/92EA-1F0F/Pictures/%1.jpg").arg(cv::getCPUTickCount());*/
                cv::imwrite(path.toLatin1().data(), m_rgb8);

                qDebug() << "save rgb image in " << path;
            }
        }


    }
    stopCapture();
}

void G400Camera::contrastStretch(float up_factor, float low_factor)
{
    Mat means, stddevs;
    meanStdDev(m_mono16_scale, means, stddevs);
    double upper_bound = means.at<double>(0) + up_factor*stddevs.at<double>(0);
    double lower_bound = means.at<double>(0) - low_factor*stddevs.at<double>(0);

    //qDebug() << upper_bound << ", " << lower_bound;


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
            if(m_mono16_scale.at<ushort>(j,i) < lower_bound)
            {
                m_mono8.at<uchar>(j,i) = 0;
            }
            else if(m_mono16_scale.at<ushort>(j,i) > upper_bound)
            {
                m_mono8.at<uchar>(j,i) = 255;
            }
            else
            {
                m_mono8.at<uchar>(j,i) = (uchar)((m_mono16_scale.at<ushort>(j,i) - lower_bound) * 255.0 / (upper_bound - lower_bound + 0.0000001));
            }
        }
    }
}

