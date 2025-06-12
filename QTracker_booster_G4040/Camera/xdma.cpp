#include "xdma.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "xdma_app_external.h"
#include "../Tool/GlobalParameter.h"  // 添加全局参数头文件

using namespace cv;

#ifdef CAMERALINK_RECV_TEST
static int cameralink_recv_test_work = 1;
pthread_t cameralink_recv_test_thread;
#endif
#ifdef SDI_SEND_TEST
static int sdi_send_test_work = 1;
pthread_t sdi_send_test_thread;
#endif
#ifdef UART_RECV_TEST
static int uart_recv_test_work = 1;
pthread_t uart_recv_test_thread;
#endif
#if defined(CAMERALINK_RECV_TEST) || defined(SDI_SEND_TEST)
static uint32_t cam_size;
static uint32_t sdi_size;
static uint32_t bytes_per_pixel;
static uint32_t bytes_per_tap;

static uint32_t width;
static uint32_t height;
static uint32_t taps;
static uint32_t bits;
static uint32_t mode;
static uint32_t num;
#endif

uint8_t *ImageBuf;
int ImageState = 0;

// 函数：将十六进制字符转换为相应的十进制数
unsigned int hexCharToUInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return 10 + c - 'A';
    if (c >= 'a' && c <= 'f') return 10 + c - 'a';
    return 0; // 对于非十六进制字符，简化处理返回0
}

// 函数：将四个字节的十六进制字符串转换为一个32位无符号整数
unsigned int hexStrToUInt(char *hex) {
    unsigned int result = 0;
    for (int i = 0; i < 8; i++) {
        result = result << 4; // 每次将结果左移4位
        result |= hexCharToUInt(hex[i]); // 将当前十六进制字符对应的数值合并到结果中
    }
    return result;
}

// Helper function to clamp values between 0 and 255
uint8_t clamp(int value) {
    if (value < 0) return 0;
    if (value > 255) return 255;
    return value;
}

// Resize an RGB image using nearest neighbor interpolation
void resize_rgb(uint8_t *src, int src_width, int src_height, uint8_t *dst, int dst_width, int dst_height) {
    for (int y = 0; y < dst_height; ++y) {
        for (int x = 0; x < dst_width; ++x) {
            int src_x = x * src_width / dst_width;
            int src_y = y * src_height / dst_height;
            int src_index = (src_y * src_width + src_x) * 3;
            int dst_index = (y * dst_width + x) * 3;
            dst[dst_index] = src[src_index];
            dst[dst_index + 1] = src[src_index + 1];
            dst[dst_index + 2] = src[src_index + 2];
        }
    }
}

// Convert an RGB image to YUYV format
void rgb_to_yuyv(uint8_t *rgb, int width, int height, uint8_t *yuyv) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; x += 2) {
            int index = y * width + x;
            int rgb_index1 = index * 3;
            int rgb_index2 = rgb_index1 + 3;

            uint8_t r1 = rgb[rgb_index1];
            uint8_t g1 = rgb[rgb_index1 + 1];
            uint8_t b1 = rgb[rgb_index1 + 2];
            uint8_t r2 = rgb[rgb_index2];
            uint8_t g2 = rgb[rgb_index2 + 1];
            uint8_t b2 = rgb[rgb_index2 + 2];

            uint8_t y1 = clamp((77 * r1 + 150 * g1 + 29 * b1) >> 8);
            uint8_t y2 = clamp((77 * r2 + 150 * g2 + 29 * b2) >> 8);
            uint8_t u = clamp((((-43 * r1 - 85 * g1 + 128 * b1) >> 8) + 128 +
                               ((-43 * r2 - 85 * g2 + 128 * b2) >> 8) + 128) >> 1);
            uint8_t v = clamp((((128 * r1 - 107 * g1 - 21 * b1) >> 8) + 128 +
                               ((128 * r2 - 107 * g2 - 21 * b2) >> 8) + 128) >> 1);

            int yuyv_index = index * 2;
            yuyv[yuyv_index] = y1;
            yuyv[yuyv_index + 1] = u;
            yuyv[yuyv_index + 2] = y2;
            yuyv[yuyv_index + 3] = v;
        }
    }
}

uint64_t read_file(char const *filename, char *buf, uint64_t size)
{
    int file_fd;
    struct stat fileStat;

    file_fd = open(filename, O_RDONLY);
    if(file_fd < 0)
      printf("%s open %s error\n", __func__, filename);

    if (stat(filename, &fileStat) == -1) {
        printf("stat %s error\n", filename);
        return -1;
    }
    if (size > fileStat.st_size) {
        printf("The size to read is greater than the length of the file\n");
        return -1;
    }

    if (lseek(file_fd, 0, SEEK_SET) == -1) {
        printf("lseek error\n");
        return -1;
    }

    if (read(file_fd, buf, size) != size) {
        printf("read %s error\n", filename);
        return -1;
    }

    if (file_fd >= 0)
        close(file_fd);

    return size;
}
void write_file(char const *filename, uint8_t *buf, uint32_t count)
{
    int rc;
    int recv_fd = open(filename, O_RDWR | O_CREAT | O_TRUNC | O_SYNC, 0666);

    if(recv_fd < 0)
      printf("open %s error\n",filename);

    rc = write(recv_fd, buf, count);
    if(rc != count)
      printf("write error, rc = 0x%x\n", rc);
    else
      printf("write success, rc = 0x%x\n", rc);

    if (recv_fd >= 0)
        close(recv_fd);
}

#ifdef UART_RECV_TEST
static void *uart_recv_test(void *p)
{
    int i, j;
    char buf[64] = {0};
    uint32_t uart_num = 1;
    uint32_t frame_len = 10;
    int val = 0;

    /*init*/
    uart_port_init(uart_num, 115200);

    while (uart_recv_test_work)
    {
        /*read kfifo*/
        val = uart_read(uart_num, buf, frame_len);
        if (val != frame_len) {
            printf("%s uart %d read error %d\n", __func__, uart_num, val);
            continue;
        }
        // Output the contents of buf, 16 bytes per line
        for (i = 0; i < 64; i += 16) {
            printf("0x%04X: ", i); // Print the address offset
            qDebug()<<"i"<<i;
        for (j = 0; j < 16; ++j) {
            printf("%02X ", (unsigned char)buf[i + j]);
            qDebug()<<"(unsigned char)buf[i + j]"<<(unsigned char)buf[i + j];
        }
        printf("\n");
    }
    if (uart_write(uart_num, buf, 10) != 10) {
        printf("%s uart write error\n", __func__);
    }

    }
    return NULL;
}
#endif
#ifdef CAMERALINK_RECV_TEST
static void *cameralink_recv_test(void *p)
{
    uint32_t count = cam_size;
    uint32_t rx_len = 0;
    int recv_frame_num = 0;
    char file_name[32];
    uint8_t *buf;

    buf = (uint8_t *)malloc(cam_size);
    if (!buf) {
        printf("%s malloc error\n", __func__);
            return NULL;
    }
    while (cameralink_recv_test_work)
    {
        //qDebug()<<"---cameralink_recv circle\n";
        rx_len = cameralink_read(buf, count);
        //qDebug()<<"---cameralink_recv "<< rx_len << recv_frame_num;
        if (rx_len != count) {
            printf("cameralink_read error\n");
            continue;
        }
        ImageBuf = buf;
        if(ImageState == 0 || ImageState == 2)
        {
            ImageState = 1;
        }
        else
        {
            ImageState = 2;
        }

//        qDebug()<<"ImageState"<<ImageState;
//        sprintf(file_name, "cameralink_recv_%d.bin", recv_frame_num);
        /* write file */
//        if (recv_frame_num < 10)
//            write_file(file_name, buf, rx_len);

        recv_frame_num++;
    }
    return NULL;
}
#endif

#ifdef SDI_SEND_TEST
static void *sdi_send_test(void *p)
{
    int src_width = CAMERALINK_IMAGE_WIDTH;
    int src_height = CAMERALINK_IMAGE_HEIGHT;
    int dst_width = SDI_IMAGE_WIDTH;
    int dst_height = SDI_IMAGE_HEIGHT;
    uint8_t *buf, *dst_rgb, *dst_yuyv;
    uint32_t count = cam_size;
    uint32_t rx_len = 0;

    buf = (uint8_t *)malloc(cam_size);
    dst_rgb = (uint8_t *)malloc(dst_width*dst_height*bytes_per_pixel);
    dst_yuyv = (uint8_t *)malloc(sdi_size);
    if (!buf || !dst_rgb || !dst_yuyv) {
        printf("%s malloc error\n", __func__);
        return NULL;
    }
/*  //改变从cameralink读取数据发送的模式，改为生成图片内容定时发送
    while (sdi_send_test_work)
    {
        rx_len = cameralink_read(buf, count);
        if (rx_len != count) {
            printf("cameralink_read error\n");
            continue;
        }
        // Resize the RGB image
        if (dst_width != src_width || dst_height != src_height) {
            resize_rgb(buf, src_width, src_height, dst_rgb, dst_width, dst_height);
            // Convert the resized RGB image to YUYV format
            rgb_to_yuyv(dst_rgb, dst_width, dst_height, dst_yuyv);
            sdi_write(dst_yuyv, sdi_size);
        } else {
            // Convert the resized RGB image to YUYV format
            rgb_to_yuyv(buf, dst_width, dst_height, dst_yuyv);
            sdi_write(dst_yuyv, sdi_size);

        }
        //write_file("sdi_save.bin", rx_buf, rx_len);
    }
*/
    int i = 0;
    
    // 获取全局参数实例，直接操作fiberTestImage
    GlobalParameter* g_param = GlobalParameter::getInstance();
    cv::Mat& image = g_param->fiberTestImage;  // 直接引用固定地址的fiberTestImage
    
    // 验证地址一致性
    qDebug() << "Thread parameter p:" << (void*)p;
    qDebug() << "fiberTestImage.data:" << (void*)image.data;
    qDebug() << "Address match:" << (p == image.data ? "YES" : "NO");
    qDebug() << "Image size:" << image.cols << "x" << image.rows;

    int fontFace = cv::FONT_HERSHEY_SIMPLEX;
    double fontScale = 1.0;
    cv::Scalar textColor=cv::Scalar(65535);
    int thickness = 2;
    cv::Point textOrg(10,30);

//    cv::Mat showimg2;
    while (sdi_send_test_work)
    {
        std::stringstream ss;
        ss << i;
        const std::string numstr = ss.str();
        cv::putText(image,numstr,textOrg,fontFace,fontScale,textColor,thickness);

        //usleep(100000);
        // 直接操作fiberTestImage的数据（现在地址固定）
        memcpy(image.data,&i,4);

        //输出连续数据 测试后删除这段代码
//        int k = 0;
//        for(int i = 0;i < 6144;i++)
//            for(int j = 0;j < 6144;j++){
//                k = j % 256;
//                memcpy(image.data+6144*i+j,&k,1);
//            }

//        image.convertTo(showimg2,CV_8UC1/*,255.0/65535.0,0*/);
//        cv::imshow("6144*6144 number",showimg2);
//        cv::waitKey(0);
//        cv::destroyAllWindows();

        i++;
        // 使用固定地址的fiberTestImage进行发送
        sdi_write((uint8_t *)image.data, sdi_size);
        //qDebug()<<"   sdi send " << i;
        //write_file("sdi_save.bin", (uint8_t *)image.data, sdi_size);
    }
    return NULL;
}
#endif

#ifdef UART_SEND_TEST
/*
 * send all frames from file
 */
static int uart_send_test(uint32_t uart_n) {
    char buf[64] = {0};
    uint32_t uart_num = uart_n;
    uint32_t count = 64;
    int file_fd;
    char *file_name = "uart_send.bin";
    int file_offset = 0;
    struct stat fileStat;
    uint64_t file_size;

    /* init */
    uart_port_init(uart_num, 115200);
    file_fd = open(file_name, O_RDONLY);
    if (file_fd < 0) {
        printf("open %s error\n", file_name);
        return -1;
    }

    if (stat(file_name, &fileStat) == -1) {
        printf("stat %s error\n", file_name);
        return -1;
    }

    file_size = fileStat.st_size;

    // Main loop to send entire file content
    while (file_offset < file_size) {
        uint32_t remaining = file_size - file_offset;
        uint32_t to_read = remaining < count ? remaining : count;

        if (lseek(file_fd, file_offset, SEEK_SET) == -1) {
            printf("%s lseek error\n", __func__);
            break;
        }

        if (read(file_fd, buf, to_read) != to_read) {
            printf("%s read %s error\n", __func__, file_name);
            break;
        }

        file_offset += to_read;
    }

    if (file_offset >= file_size) {
        printf("%s has been sent successfully\n", file_name);
    }
    // Cleanup
    if (file_fd >= 0)
        close(file_fd);

    return 0;
}
#endif
static void sync_module_test(void)
{
    // rising edge
    int polarity_in = 0;
    // rising edge
    int polarity_out = 0;
    // 12.5MHz(10*8ns)
    //int sync_freq_out = 12500000;
    // 10KHz(10*8ns)
    int sync_freq_out = 10000;
    // 40ns
    //double sync_duty_out = 4e-8;
    // 40ns
    double sync_duty_out = 5e-5;

    sync_input_polarity_sel(polarity_in);
    sync_out_polarity_sel(polarity_out);
    sync_freq_out_set(sync_freq_out);
    sync_duty_out_set(sync_duty_out);
    sync_module_enable();
}

static void central_crosshair_test(void)
{
    int flag = 1;
    //int row = 540, col = 960, len = 500;
    int row = 960, col = 540, len = 500;

    central_crosshair_pos_set(row, col);
    central_crosshair_len_set(len);
    central_crosshair_set(flag);
}

static void target_crosshair_test(void)
{
    int i, flag = 1;
    int row = 100, col = 100, len = 100;

    for (i = 0; i < 10; i++ )
    {
        //target_crosshair_pos_set(i, (row + 50*i), (col + 100*i));
        target_crosshair_pos_set(i, (col + 20*i), (row + 100*i));
        target_crosshair_len_set(i, len);
        target_crosshair_set(i, flag);
    }
}
#define WIDTH 64
#define HEIGHT 64

void read_pixel_file(const char *filename, uint8_t pixels[HEIGHT][WIDTH / 8])
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH / 8; j++) {
            fscanf(file, "%2hhx", &pixels[i][j]);
        }
    }

    fclose(file);
}

static void char_data_test(void)
{
    int i;
    int col = 100, row = 100;
    int space = 20;
    uint8_t pixels[HEIGHT][WIDTH/8] = {0};
    char file_name[32];

    character_data_size_set(WIDTH, HEIGHT);
    character_data_space_set(space, 1);
    character_data_space_set(space, 0);
    character_data_position_set(col, row, 1);
    character_data_position_set(col, row, 0);

    for (i = 0; i < 4; i++ )
    {
        sprintf(file_name, "zimo%d.txt", i);
        FILE *file = fopen(file_name, "r");
        if (!file) {
            perror("Failed to open file");
            return;
        }
        read_pixel_file(file_name, pixels);
        character_data_set(i, 1, HEIGHT*WIDTH/8, (uint8_t *)pixels);
        //character_data_set(i, 0, count, buf);
    }
    character_data_set_complete();
}

//static void func_sig_int(int sig)
//{
//    printf("Received Ctrl+c\n");
//#ifdef SDI_SEND_TEST
//    sdi_send_test_work = 0;
//#endif
//#ifdef UART_RECV_TEST
//    uart_recv_test_work = 0;
//#endif
//    xdma_app_receive_stop();
//    exit(0);
//}

static void print_usage(void)
{
    printf("========xdma test app========\n");
    printf("Build time: %s %s\n", __DATE__,__TIME__);
    printf("help infomation:\n");
    printf("'q': quit\n");
    printf("'u': uart 0 send test\n");
    printf("=======================\n");

}


uint8_t *outputMat()
{
    return ImageBuf;
}

int outputImageState()
{
    return ImageState;
}

int xdma_send_start(const uint16_t *image)
{
    if (xdma_app_init() != 0) {
        printf("%s: xdma_app_init error\n", __func__);
        return -1;
    }
    if (image_init(width, height, taps, bits, mode, num) != 0) {
        printf("%s: image_init error\n", __func__);
        return -1;
    }
    xdma_event_init();

    // Calculate the size of the image
    bytes_per_pixel = (bits == 8 ? 1 : 2);
    bytes_per_tap = (taps == 3 ? 3 : 1);
    cam_size = width*height*bytes_per_pixel*bytes_per_tap;
    // yuyv422 8bits
    sdi_size = width*height*2*bytes_per_tap;

    qDebug()<<"________________________________________";
    #ifdef SDI_SEND_TEST
        pthread_create(&sdi_send_test_thread, NULL, sdi_send_test, (void*)image);
    #endif
    #ifdef UART_RECV_TEST
        pthread_create(&uart_recv_test_thread, NULL, uart_recv_test, NULL);
    #endif

//        signal(SIGINT, func_sig_int);

//        while (inp != 'q')
//        {
//            inp = getchar();

//           switch (inp) {
//    #ifdef UART_SEND_TEST
//            case 'u':
//                uart_send_test(0);
//                printf("Sending data on UART %d\n", uart_num);
//               break;
//    #endif
//            case 'a':
//                sync_module_test();
//                break;
//            case 'b':
//                central_crosshair_test();
//                break;
//            case 'c':
//                target_crosshair_test();
//                break;
//            case 'd':
//                char_data_test();
//                break;

//           default:
//                break;
//            }
//        }

//    #ifdef CAMERALINK_RECV_TEST
//        pthread_join(cameralink_recv_test_thread, NULL);
//    #endif
//    #ifdef SDI_SEND_TEST
//        pthread_join(sdi_send_test_thread, NULL);
//    #endif
//    #ifdef UART_RECV_TEST
//        pthread_join(uart_recv_test_thread, NULL);
//    #endif
 //       xdma_app_receive_stop();
  return 0;
}

int xdma_send_stop()
{
    sdi_send_test_work = 0;
}

int xdma_receive_proc()
{
    if (xdma_app_init() != 0) {
        printf("%s: xdma_app_init error\n", __func__);
        return -1;
    }
    if (image_init(width, height, taps, bits, mode, num) != 0) {
        printf("%s: image_init error\n", __func__);
        return -1;
    }
    xdma_event_init();

    // Calculate the size of the image
    bytes_per_pixel = (bits == 8 ? 1 : 2);
    bytes_per_tap = (taps == 3 ? 3 : 1);
//    cam_size = width*height*bytes_per_pixel*taps;
 //   cam_size = width*height*bytes_per_pixel* bytes_per_tap;
    cam_size = width*height*bytes_per_pixel*bytes_per_tap;
    // yuyv422 8bits
    sdi_size = width*height*2;
    qDebug()<<"________________________________________";
#ifdef CAMERALINK_RECV_TEST
    cameralink_recv_test_work = 1;
    pthread_create(&cameralink_recv_test_thread, NULL, cameralink_recv_test, NULL);
#endif
    return 0;
}

void closecameralink_recv()
{
#ifdef CAMERALINK_RECV_TEST
    qDebug()<<"---begin close cameralink_recv_test_thread "<< cameralink_recv_test_thread;
    cameralink_recv_test_work = 0;
//    if(cameralink_recv_int_count >0)
    pthread_join(cameralink_recv_test_thread, NULL);
    qDebug()<<"---close cameralink_recv_test_thread end";
#endif
}

void GetCameraParam(uint32_t Width, uint32_t Height, uint32_t Taps, uint32_t Bits, uint32_t Mode, uint32_t Num)
{
    width = Width;
    height = Height;
    taps = Taps;
    bits = Bits;
    mode = Mode;
    num = Num;
}
