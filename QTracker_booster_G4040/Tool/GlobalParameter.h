#ifndef GLOBALPARAMETER_H
#define GLOBALPARAMETER_H

#include <QDebug>
#include <QSettings>
#include <QFile>
#include<QMutex>
#include <QWaitCondition>
#include <opencv2/opencv.hpp>
#include "DataCacheQueue.h"
#include <QHostAddress>

using namespace std;
using namespace cv;

/// 20190626 wangzy fixed IR camera image size
///
#define IR_WIDTH 640
#define IR_HEIGHT 512

#define VS_WIDTH 1920
#define VS_HEIGHT 1080
//#pragma pack(push,1)
struct DetectResult
{
    vector<string> classNamesVec;
    vector<cv::Rect> boxes;
    vector<int> classNamesID;
    vector<float> prob;
    vector<string> classNamesVec_CC;
    vector<cv::Rect> boxes_CC;
    vector<int> classNamesID_CC;
    vector<float> prob_CC;
    vector<double> centroidsX_CC;
    vector<double> centroidsY_CC;
    vector<double> sumgray;
};

/// Ŀ������ʶ��״̬
enum TRACK_STATE
{
    IDLE = 0, /// do nothing
	DETECT = 1, /// ����ʶ���׶�
	TRACK = 2, /// �ջ�����
	PREDICT = 3, /// ��������
};

/// Ŀ�������㷨
enum TRACK_METHOD
{
	TRACK_KCF_HC = 1, /// ���߶�KCF������CN����
    TRACK_KCF = 2, /// traditional kcf
	TRACK_ECO_HC = 3, /// ECO-HC
};

/// ͼ����ǿ
enum IMAGE_ENHANCE
{
	NONE = 0, /// ��
	EQU_HIST = 1, /// ֱ��ͼ���⻯
};

enum IMAGE_SOURCE
{
    VISUAL = 1, /// ��Ƶ�ļ�
    IR = 2, /// ��������
    IR1 = 3,
    IR2 = 4,
};

struct DisplayParam
{
	IMAGE_SOURCE imgSource;
	cv::Point2i mouseClickPos; /// ��������ͼ�����꣬��һ������������ϵ�����Ͻ�Ϊ��0,0����
    cv::Point2d imgScale; /// 20180712 wangzy
    cv::Size2i imgSize; /// ��ǰ����Դͼ��ԭʼ�ߴ磬�ǳ���Ҫ��;
    int fps; /// 20Hz

    cv::Size2i VS_size;
    cv::Size2i IR_size;
    int VS_cam_port; /// 20190716 wangzy
    int small_win_size; /// 20190720 wangzy
    int small_win_size1;
    int small_win_pos; /// 20191019 wangzy  0:left-up  1:right-up  2:right-down  3:left-down

    float IR_up_factor;
    float IR_low_factor;
};

struct TrackParam
{
    TRACK_STATE state; /// state
    TRACK_METHOD method; ///

    //IMAGE_ENHANCE enhance; ///

    bool bManualSelect; /// prio
    bool bAutoDetect2Track; ///
    bool bChangeTrackGateSize; /// 20191026 wangzy
    
    cv::Point2f objPosPix; /// (0,0) at left-up corner within image
    cv::Point2d optPosPix; ///
	
    cv::Rect2d searchGateRoi; /// unuse
	cv::Size2d searchGateSize;

    cv::Rect2d trackGateRoi; /// (0,0) at left-up corner within image
	cv::Size2d trackGateSize;

    float psr;

    double thresh_lost; /// 6.0
    double thresh_occlude; /// 20.0
    int occlude_time; /// 40

    /// detect
    float thresh_conf; /// 20190808 wangzy
    float thresh_nms;
    int detect_num; /// 20190806 wangzy

    QString sn; /// 20190812 wangzy
    bool use_scale; /// 20190826 wangzy
    bool use_full_net;
    int detect_type; /// 20191212 wangzy

    bool bBlackDetect; //rgb2black dectect
    bool bSendServer;

    //GaoSu Trigger
    int triggerIndex1;
    int triggerNum1;
    int triggerIndex2;
    int triggerNum2;
    int triggerIndex3;
    int triggerNum3;
    unsigned char triggerRelation;
    bool bTriggerEnable;

    //Detect To Auto Track
    int autoTrackIndex1;
    int autoTrackNum1;
    int autoTrackIndex2;
    int autoTrackNum2;
    int autoTrackIndex3;
    int autoTrackNum3;
   // bool bAntoTrackEnable;

    //traditonal detect
    double thresValueTrad;
    bool   bAutoThresTrad;
    int    minSizeTrad = 12;
    int    maxNumTrad;
    int    modeValueTradition;

    bool bTrackTradition;
    double detect_conf;
};

struct ServoXXTParam
{
    int guideMode;
};

struct ControlParam
{
    bool power_on;
    bool acq_image;
    bool pro_image;
    bool short_long;
    bool twebit_image;
    bool full_image;
    QString TriggerMode;
    int Register1208;
    int Timing;
    bool focusing;
    QString freq_image;
    float temp_set;
    QString nmbbh;
    QString nshbh;
    QString fix_exp_time;
    QString short_exp_time;
    QString long_exp_time;
    bool saveIPD;
    bool AutoThresTrad;
    QString ThreshValue;
    QString MinSizeW;
    QString MinSizeH;

    bool CDDPowerOn;
    QString MBBH;
    QString Pass;
    QString SHBH;
    QString Temperature;
    QString Humidity;
    QString Pressure;
    bool ShowImage;
    float FS;
    int Numfailtri;
    short ReadTimHalf;
    float TempParama;
    float TempParamb;
    bool Comserialport;
    int m_TCPTuPort;
    int m_UDPTuPort;
    QString udpAddr;
    QString lAddr;
    int m_lUDPTuPort;
    QString qSerialPort;
    QString TestCameraState;
    int TestCameraBaud;
    int SerialPortdatalen;
    bool TCPOPEN;
};
//#pragma pack(push,1)
struct Struct_CCD_Control_In
{
    unsigned char chParametersBegin;
    bool bCCDPowerOn;
    bool bAcquireImage;
    bool bShowImage;
    bool bImageProccess;
    bool bShortAndLongExp;
    bool bTwelveBitImage;
    bool bFullImageScan;
    unsigned char nImageFreq;
    float fChipTempSet;
    unsigned int nMBBH;
    char nPass;
    unsigned short nSHBH;
    unsigned short nFixExptime;
    unsigned short nShortExpTime;
    unsigned short nLongExptime;
    float fTemperature;
    float fHumidity;
    float fPressure;
    char nEMGain;
    float fAZeroError;
    float fEZeroError;
    char chBak[41];
    unsigned char chParametersEnd;
};

struct FocusParam
{
    int image_w;
    int image_h;
    bool mouseDoubleClick = false;
};

struct DebugParam
{
	long inputCount; /// ����ͼ������
	long processCount; /// ����ͼ������
	long displayCount; /// ��ʾͼ������

	double avgProcessTime; /// ʵʱ��¼�㷨��ʱ

    float processFPS;
    int detectNum;
    bool  bTrackAndDetect;

    bool bSaveRawFileOnceGrab;
};

struct CameraConfigParam
{
    int ResolutionW = 4096;
    int ResolutionH = 4096;
    int CameraLinkMode = 0;
    int ImageBit = 16;
    int ImageTap = 1;
    int ImageFormat = 0;
    bool CameraLive = false;
};

struct PCControlParam
{
    bool b_LongWaveCamera = false;
    bool b_MediumWaveCamera = false;
    bool b_MediumWaveInfraredCamera = false;
    bool b_VisibleLightCamera = false;

    bool TrackingState = false;
    int TrackingPointX;
    int TrackingPointY;
    bool EleImageStab = false;
    bool ImageEnhancement = false;
    bool SetGate = false;
    int GateSize;
    bool SetTrackGate = false;
    int TrackGateSize;
    bool CrossSilkDisplay = false;
    bool CharacterDisplay = false;
    bool TargetDetectState = false;
    bool GatePosition = false;
    int GatePositionTurn;
    bool TrackingMode = false;
    int TrackingPoint;

    int sys_state = 0; //0 idle   1: send    2: receive
};

/**
* @brief �̰߳�ȫ��ȫ�ֲ����࣬ά��ϵͳ���ò����͹������档����Singleton����ģʽ�����ڴ�й¶��
* @date 2018/03/05
* @version 1.0
* @author Wangzy
*/
class GlobalParameter
{
public:
	/**
	* @brief �ṩΨһȫ�ַ��ʽӿ�
	* @return ��̬��ָ��
	*/
	static GlobalParameter* getInstance();
	/**
	* @brief ���Լ���������
	* @param
	* @return 
	*/
	void resetDebugCount();
	/**
	* @brief ���乫���ڴ棬��������Դʱ��������
	* @param
	* @return
	*/
	void allocateMemory();

    void loadConfigFile(QString path);
    //void ControlConfigFile(QString path1);
private:
	/**
	* @brief ˽�й��캯����ֹ��ʵ����
	*/
	GlobalParameter();
	/**
	* @brief ϵͳ�Զ�����
	*/
	~GlobalParameter();
public:
    void ControlConfigFile(QString path1);
	/// ͼ����ʾ����
	DisplayParam displayParam;
    /// track config
	TrackParam trackParam;
	/// ���Բ���
	DebugParam debugParam;
    /// control
    ControlParam controlParam;
    Struct_CCD_Control_In struct_ccd_control_in;
    ///fouse
    FocusParam focusParam;
    ///cameraconfig
    CameraConfigParam cameraconfigParam;
    ///PCControl
    PCControlParam pccontrolparam;

	/// ͼ�񻺴�����
	//DataCacheQueue<Mat> imageTrackQueue;
	//DataCacheQueue<Mat> imageSaveQueue;

    DataCacheQueue<Mat> imageProcessQueue_VS; /// 20190605 wangzy
    DataCacheQueue<Mat> imageProcessQueue_IR; /// 20190605 wangzy


    DataCacheQueue<Mat> imageDetectQueue;

    DataCacheQueue<Mat> imageDisplayQueue;

    ServoXXTParam servoXXTParam;
    /// capture
    Mat imageCapture;

    // fiber test Mat
    Mat fiberTestImage;

    /// draw UI
	Mat imageDisplay;
    Mat imageDisplay_small;

    /// yolo
    DetectResult yolo_res;

    /// key
    QString key = "19:86:03:17:00:11";

    QMutex saveimageMutex;
    QWaitCondition saveimageWaitCondition;
    int exp_num_ini = 0;
    bool detect_flag = false;
    int focus = 0;
    bool focus_flag = false;
    //QByteArray buf_a;
    QByteArray buf_a,buf_b;
    QString bufdata_st,bufdata_j,bufdata_w,bufdata_hb,bufdata_ms;
    double ang_elevatio,ang_azimuth;
    double realtime_ang_elevatio,realtime_ang_azimuth;
    double Longitude,Latitude;
    double expose_ipd;
    QString expmode;
    bool sign_saveIPD = true;
    bool AutoThresTrad = true;
    float ThreshVM;
    QString shbh,mbbh,pass;
    double Tem,Hum,Press;
    QString bufdata_name1;
    bool show;
    int iiiiii = 0;
    double exp = 0,short_exp = 0,long_exp = 0;
    QString T ;
    int gain_index = 0;
    double shortexp =0;
    double longexp = 0;
    QString file_name,file_name_ipd,file_name1,file_name2;
    bool time_dat = false;
    Mat m16;
    double expouse;
    bool flag_mat = true;
    QString hz;
    bool flag_copyover = false;
    bool flag_hz = false;
    int sifu = 0;
    bool savesifu = false;
    double azimuth[100] = {0},elevatio[100] = {0};
    bool zero = false;
    QString current_date,current_date2,current_data_saveover,old_date;
    QString current_time,current_time2,current_time3,current_time_saveipd,current_time_saveover;
    bool shijianjiaozhun = false;
    int kk = 10;
    bool flag_stop = false;
    int miss_time;
    int mis_tim = 0;
    bool save_control = true;
    QString name_S,name_L,name_S_ipd,name_L_ipd;
    bool startsaveIPD = true;
    double bkdValue1,bkdValue2,bkdValue3,bkdValue4,bkdValue5,bkdValue6,bkdValue7,bkdValue8,bkdValue9 = 0;
    bool savefitsimage = false;
    QString bufdata_stexp;
    bool expTriFlag = false;
    int expcs = 0;
    short fs;
    double azimuth_a = 0,azimuth_b = 0,azimuth_c = 0,elevatio_a = 0,elevatio_b = 0,elevatio_c = 0;
    bool setexperror = false;
    int tmp;
    bool ready_power = false;
    short ReadTimHalf;
    bool savetiff = false;
    bool saveraw = false;
    bool savejpg = false;
    bool savefits = false;
    bool startsavejpg = false;
    bool startsavetiff = false;
    bool startsaveraw = false;
    bool startsavefits = false;
    bool b_savefits = false;
    int gain = 0;
    unsigned int FreeStoreSize = 0;
    bool savestandardfits_flag = true;
    double camerafps;
    Mat hist = Mat::zeros(1,1000,CV_16UC1);
    bool AuxiliaryLine = false;
    bool bShowBit = false;
    bool bShowSkyRight = false;
    //cv::Point2i mousePressPos;
//    bool m_LeftButton = false;
    int grayval = 0;
    bool m_remove_bkd = false;
    bool m_store_bkd_once = false;
    bool b_showBackgroundMap = true;
    int Width = 0;
    int Height = 0;
    bool b_G4040Camera = false;
    bool b_G400Camera = false;
    bool b_USBCamera = false;
    bool b_C640Camera = false;
    int num = 0;
    bool HintClose = true;

    QString XCAP = "../CAMERACONTROL/xcvidset.fmt";
    bool EstimateGather = true;
    int MeanBackgroundFps = 1;
    double threstradV;
    QString LoadPath;
    bool ImageProcessingdisplaystart = false;
    bool ImageProcessingdisplayend = false;
    QString MeanValue = "0";
    QString Variance = "0";
    QString MaxGrayValue = "0";
    QString MinGrayValue = "0";
    bool StartMeasurement = false;
    cv::Point2i MeasuremenStartmouseClickPos;
    cv::Point2i MeasuremenEndmouseClickPos;
    int MeasurementState = 0;
    int MeasurementShape = 0;
    bool Measurement = false;
    QString MeasurementStartX,MeasurementStartY,MeasurementEndX,MeasurementEndY;
    QString HorizontalDistance,VerticalDistance,RegionalArea;
    bool setusbcameraexpok = true;
    bool setusbcameragainok = true;
    double usbexp = 0;
    int star_num;

    int i_setC640CameraImagebitdepth = 1;
    int C640CameraModeState = 0;            //ITR
    int C640CameraTirModeState = 0;         //int Tir
    int C640CameraExpTime = 2000;           //Exptime(us)
    int C640CameraFPS = 50;                 //FPS 50
    bool C640CameraMode = false;
    int i_setC640CameraImageCalibration = 5;
    bool b_setC640CameraSinglePointCorrection = false;
    int i_setC640CameraIntegralGear = 0;
    bool b_QueryStatusButton = false;

    QString ReadMode,ReadTir,ReadExp,ReadFPS,ReadVideoMode,ReadScreen;

    QString ReadWorkGears;

    bool setNUC2DState = false;
    bool setNUC2DStategreen = false;
    bool setNUC2DStatered = false;
    bool setNUC2DStateyellow = false;
    int setNUC2DStatenum = 0;

    bool setC640CameraReset = false;

    bool startserial = true;
    bool readserialend = false;

    int i_setImageBitShow = 0;

    char* framebuffer;
    char* tempbuffer;

    int adjFps = 1;

    bool uart_recv_work = false;

};

#endif // GLOBALPARAMETER_H
