#include "GlobalParameter.h"

GlobalParameter* GlobalParameter::getInstance()
{
    static GlobalParameter instance;
    return &instance;
}

void GlobalParameter::resetDebugCount()
{
    debugParam.inputCount = 0;
    debugParam.processCount = 0;
    debugParam.displayCount = 0;
    debugParam.bTrackAndDetect    = false;
}

void GlobalParameter::allocateMemory()
{
    /// ?????????????
    imageProcessQueue_VS.clear();
    imageProcessQueue_IR.clear();
    imageDetectQueue.clear();
    imageDisplayQueue.clear();
    imageProcessQueue_VS.setMaxCount(2);
    imageProcessQueue_IR.setMaxCount(2);
    imageDetectQueue.setMaxCount(2);
    imageDisplayQueue.setMaxCount(2);
}

void GlobalParameter::loadConfigFile(QString path)
{
    if(!QFile(path).exists())
    {
        qDebug() << path << " file load error!";
        return;
    }
    QSettings set(path, QSettings::IniFormat);

    QStringList group = set.childGroups();
    if(group.size() < 3)
    {
        qDebug() << "load group error";
        return;
    }
    /// detect
    set.beginGroup("Detect");
    trackParam.thresh_conf = set.value("thresh_conf").toFloat();
    trackParam.thresh_nms = set.value("thresh_nms").toFloat();
    trackParam.detect_num = set.value("detect_num").toInt();
    set.endGroup();
    /// display
    set.beginGroup("Display");
    displayParam.VS_size.width = set.value("VS_width").toInt();
    displayParam.VS_size.height = set.value("VS_height").toInt();
    displayParam.IR_size.width = set.value("IR_width").toInt();
    displayParam.IR_size.height = set.value("IR_height").toInt();
    displayParam.IR_up_factor = set.value("IR_up_factor").toFloat();
    displayParam.IR_low_factor = set.value("IR_low_factor").toFloat();
    displayParam.fps = set.value("fps").toInt();
    displayParam.VS_cam_port = set.value("VS_cam_port").toInt();
    displayParam.small_win_size = set.value("small_win_size").toInt();
    displayParam.small_win_size1 = set.value("small_win_size").toInt();
    displayParam.small_win_pos = set.value("small_win_pos").toInt();
    set.endGroup();
    /// track
    set.beginGroup("Track");
    trackParam.trackGateSize.width = set.value("track_roi_width").toInt();
    trackParam.trackGateSize.height = set.value("track_roi_height").toInt();
    trackParam.thresh_lost = set.value("thresh_0").toDouble();
    trackParam.thresh_occlude = set.value("thresh_1").toDouble();
    trackParam.occlude_time = set.value("thresh_3").toInt();
    trackParam.sn = set.value("sn").toString();
    trackParam.use_scale = set.value("use_scale").toBool();
    //trackParam.detect_type = set.value("detect_type").toInt();
    set.endGroup();

}


void GlobalParameter::ControlConfigFile(QString path1)
{
    if(!QFile(path1).exists())
    {
        qDebug() << path1 << " file load error!";
        return;
    }
    QSettings set(path1, QSettings::IniFormat);

    QStringList group = set.childGroups();
    if(group.size() < 1)
    {
        qDebug() << "load group error";
        return;
    }
    /// control
    set.beginGroup("CCD_Control");
    controlParam.power_on = set.value("bCCDPowerOn").toBool();
    controlParam.acq_image = set.value("bAcquireImage").toBool();
    controlParam.pro_image = set.value("bImageProccess").toBool();
    controlParam.short_long = set.value("bShortAndLongExp").toBool();
    controlParam.twebit_image = set.value("bTwelveBitImage").toBool();
    controlParam.full_image = set.value("bFullImageScan").toBool();
    controlParam.TriggerMode = set.value("bTriggerMode").toString();
    controlParam.Register1208 = set.value("bRegister1208").toInt();
    controlParam.Timing = set.value("nTiming").toInt();
    controlParam.freq_image = set.value("nImageFreq").toString();
    controlParam.temp_set = set.value("fChipTempSet").toFloat();
    controlParam.nmbbh = set.value("nMBBH").toString();
    controlParam.nshbh = set.value("nSHBH").toString();
    controlParam.fix_exp_time = set.value("nFixExptime").toString();
    controlParam.short_exp_time = set.value("nShortExpTime").toString();
    controlParam.long_exp_time = set.value("nLongExptime").toString();
    controlParam.focusing = set.value("bFocusing").toBool();
    controlParam.saveIPD = set.value("bSaveIPD").toBool();
    controlParam.AutoThresTrad = set.value("bAutoThresTrad").toBool();
    controlParam.ThreshValue = set.value("nThreshValue").toString();
    controlParam.MinSizeW = set.value("nMinSizeW").toString();
    controlParam.MinSizeH = set.value("nMinSizeH").toString();
    controlParam.CDDPowerOn = set.value("bCDDPowerOn").toBool();
    controlParam.MBBH = set.value("nMBBH").toString();
    controlParam.SHBH = set.value("nSHBH").toString();
    controlParam.Pass = set.value("nPass").toString();
    controlParam.Temperature = set.value("fTemperature").toString();
    controlParam.Humidity = set.value("fHumidity").toString();
    controlParam.Pressure = set.value("fPressure").toString();
    controlParam.ShowImage = set.value("bShowImage").toBool();
    controlParam.FS = set.value("sFS").toFloat();
    controlParam.Numfailtri =set.value("nNumfailtri").toInt();
    controlParam.TempParama = set.value("fTempParama").toFloat();
    controlParam.TempParamb = set.value("fTempParamb").toFloat();
    controlParam.Comserialport = set.value("bComserialport").toBool();
    controlParam.TCPOPEN = set.value("bTCPOPEN").toBool();
    controlParam.m_TCPTuPort = set.value("TCPPORT").toInt();
    controlParam.m_UDPTuPort = set.value("UDPPORT").toInt();
    controlParam.udpAddr = set.value("TCPUDPADDRSTR").toString();
    controlParam.lAddr = set.value("LADDRSTR").toString();
    controlParam.m_lUDPTuPort = set.value("LUDPPORT").toInt();
    controlParam.qSerialPort = set.value("SERIALPORT").toString();
    controlParam.TestCameraState = set.value("STestCameraState").toString();
    controlParam.TestCameraBaud = set.value("nTestCameraBaud").toInt();
    controlParam.SerialPortdatalen = set.value("SERIALPORTDATALEN").toInt();
    QHostAddress m_xingTuAddr = QHostAddress(controlParam.udpAddr);
    qDebug()<<"!!!!!!!!!!!!!!!"<<controlParam.m_TCPTuPort<<":"<<m_xingTuAddr;

    set.endGroup();
}

GlobalParameter::GlobalParameter()
{

    framebuffer=NULL;
    framebuffer=new char[1920*1080*3];
    memset(framebuffer,0,1920*1080*3);

    tempbuffer=NULL;
    tempbuffer=new char[1920*1080*2];
    memset(tempbuffer,0,1920*1080*2);

    allocateMemory();

    /// ?????????
    memset((void*)&displayParam, 0, sizeof(DisplayParam));
    displayParam.imgScale.x = 1.0;
    displayParam.imgScale.y = 1.0;
    displayParam.imgSource = VISUAL;
    displayParam.imgSize = cv::Size2i(VS_WIDTH, VS_HEIGHT);
    displayParam.IR_size = cv::Size2i(IR_WIDTH, IR_HEIGHT);
    displayParam.VS_size = cv::Size2i(VS_WIDTH, VS_HEIGHT);
    displayParam.fps = 20;
    displayParam.IR_up_factor = 4.0f;
    displayParam.IR_low_factor = 1.0f;
    displayParam.VS_cam_port = 6;
    displayParam.small_win_pos = 1;
    /// ????????????
    trackParam.bManualSelect = false;
    trackParam.bAutoDetect2Track = false;
    trackParam.bChangeTrackGateSize = false;
    trackParam.searchGateSize = cv::Size2d(512,512);
    trackParam.trackGateSize = cv::Size2d(128, 128);
    trackParam.trackGateRoi = cv::Rect2d(0, 0, 0, 0); /// 20190720 wangzy
    trackParam.state = DETECT;
    trackParam.method = TRACK_KCF; /// TRACK_KCF
    trackParam.detect_conf = 0.3;
    trackParam.thresh_lost = 0.1;
    trackParam.thresh_occlude = 0.15;
    trackParam.occlude_time = 10;
    trackParam.detect_num = 7;
    trackParam.thresh_conf = 0.3f;
    trackParam.thresh_nms = 0.2f;
    trackParam.sn = "0000-0000-0000-0000";
    trackParam.detect_type = 1;
    trackParam.bBlackDetect = false;
    trackParam.triggerRelation = 0x00;
    trackParam.bTriggerEnable = false;
    trackParam.bAutoThresTrad = true;
    trackParam.thresValueTrad = 127;
    trackParam.minSizeTrad = 5;
    trackParam.modeValueTradition = 0;
    trackParam.bTrackTradition = true;


    /// ????????????
    focusParam.image_h = 200;
    focusParam.image_w = 200;
    resetDebugCount();
    debugParam.bSaveRawFileOnceGrab = false;


    servoXXTParam.guideMode = 1;

    loadConfigFile("./cfg/config.ini");
    ControlConfigFile("./cfg/control.ini");
}


GlobalParameter::~GlobalParameter()
{
    if(NULL != framebuffer)
    {
        delete framebuffer;
        framebuffer = NULL;
    }
    if(NULL != tempbuffer)
    {
        delete tempbuffer;
        tempbuffer = NULL;
    }
}
