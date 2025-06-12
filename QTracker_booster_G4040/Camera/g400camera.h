#ifndef G400CAMREA_H
#define G400CAMREA_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QString>
#include <QTimer>
#include <QDataStream>
#include <QDateTime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <QImage>
#include <QStorageInfo>
#include "camerabase.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "xdma.h"

/*
 *  NECESSARY INCLUDES:
 */
#include <stdio.h>		// c library
#include <signal.h>		// c library
#include <stdlib.h>		// c library
#include <stdarg.h>		// c library
#include <unistd.h>		// c library
#include <limits.h>		// c library

using namespace cv;

extern QList<uchar*> rev_List;

const int g400_width = 4096;
const int g400_height = 4096;

void *WrapperUartRecvA(void *arg);
void *WrapperUartSendA(void *arg);

void *WrapperUartRecvB(void *arg);
void *WrapperUartSendB(void *arg);

#define UART_PORT_A                    1
#define UART_PORT_B                    2
class G400Camera : public CameraBase
{
    Q_OBJECT
public:
    G400Camera();
    ~G400Camera();
    bool init();
    void close();
    void stopsend();
    void startCapture();
    void stopCapture();
    bool readCurrentFrame();

    void starReceive();
    void stopReceive();

    void bufToRGB();
    void getFiberTestImage();

    pthread_t pthreadUartRecvA;
    bool f_threadUartRecvA = false;
    void UartRecvProcessA();

    pthread_t pthreadUartSendA;
    bool f_threadUartSendA = false;
    void UartSendAProcess();

    pthread_t pthreadUartRecvB;
    bool f_threadUartRecvB = false;
    void UartRecvProcessB();

    pthread_t pthreadUartSendB;
    bool f_threadUartSendB = false;
    void UartSendBProcess();



    unsigned int read_uart(unsigned char port, char *buff);
    void portRecv();
    void sendToUart(unsigned char port, const char *data, unsigned int len);
    void exampleSendUart();

signals:
     void SignalGrabData();
protected:
    void run();
private:
    bool contrastStretch(float up_factor, float low_factor);
    ushort DataTransfer(const ushort indata);

    bool WriteFitsFile(char *str_filename,int nW,int nH,int bingmode[4],double expTime,int obsTime[7],double obsPos[4],double ObsInf[9],double dbIXY[2],ushort *lpDif,bool bStandard);
private:
    //ushort* m_mono16_raw; /// original image
//    Mat m_mono16;
//    Mat m_mono16_scale;
    Mat m_mono8;
    Mat m_rgb8;
//    Mat m_mono16_bkd;
//    Mat m_mono16_bin;
//    Mat m_mono8_jd;
//    Mat m_rgb_jd;
//    Mat m_mono16bkd1;
//    Mat m_mono16bkd2;
//    Mat m_mono16bkd;

    int m_img_width; /// image size
    int m_img_height;
    //cv::Mat m_img_mono8;
    bool m_store_RemoverFPN_once;
    bool m_store_FPN_OK;
    double exposure;
    int v = 6;
    bool ready_START = false;
    int meanbkdnum = 0;
    double weight = 1;

    double time_fps_counter = 0;
    double totalFramefps = 0;
    bool bRefreshTime;
    int usbgain = 0;
    double grayval = 0;

    QTimer *timerSoftTriggerInc;

    uint32_t camera_cam_size;
    uint32_t _bytes_per_pixel;
    uint32_t _bytes_per_tap;
    uint32_t _count;
    uint32_t m16count;
    uint8_t *_buf;
    Mat curMat;
    Mat curMat_scale;
    int _width;
    int _height;
    int rev_ImageState = 0;

};

#endif // G400CAMREA_H
