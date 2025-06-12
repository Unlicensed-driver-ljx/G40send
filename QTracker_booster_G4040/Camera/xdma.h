#ifndef XDMA_H
#define XDMA_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>
#include <memory.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include "xdma_app_external.h"
#include <QDebug>
#include <QObject>
#include "camerabase.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "Tool/GlobalParameter.h"

#define CAMERALINK_RECV_TEST
#define SDI_SEND_TEST
//#define UART_SEND_TEST
//#define UART_RECV_TEST

void init_lookup_tables();
int xdma_send_start(const uint16_t *image);
int xdma_send_stop();
int xdma_update_address(const uint16_t *new_address);
int xdma_receive_proc();
void closecameralink_recv();
void GetCameraParam(uint32_t Width, uint32_t Height, uint32_t Taps, uint32_t Bits, uint32_t Mode, uint32_t Num);
uint8_t *outputMat();
int outputImageState();


//class xdma : public CameraBase
//{
//public:
//    xdma();
//    ~xdma();
//protected:
//    void run();
//private:
//    bool readCurrentFrame();
//private:
//    cv::Mat m_rgb8;
//    int m_img_height;
//    int m_img_width;
//public:
//    bool init();
//    void close();
//    void startCapture();
//    void stopCapture();
//};

#endif // XDMA_H
