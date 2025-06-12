#include "onlinetunedialog.h"
#include "ui_onlinetunedialog.h"
#include "../Camera/xdma.h"

OnlineTuneDialog::OnlineTuneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnlineTuneDialog)
{
    ui->setupUi(this);
    g_param = GlobalParameter::getInstance();

    connect(ui->pushButtonCameraState, SIGNAL(clicked()), this, SLOT(onC640CameraState()));

    connect(ui->lineEditResolutionW,&QLineEdit::editingFinished,this,[=](){
        g_param->cameraconfigParam.ResolutionW = ui->lineEditResolutionW->text().toInt();
    });

    connect(ui->lineEditResolutionH,&QLineEdit::editingFinished,this,[=](){
        g_param->cameraconfigParam.ResolutionH = ui->lineEditResolutionH->text().toInt();
    });

    connect(ui->spinBoxImageBit, SIGNAL(valueChanged(int)), this, SLOT(CameraSetImageBit(int)));
    connect(ui->spinBoxImageTap, SIGNAL(valueChanged(int)), this, SLOT(CameraSetImageTap(int)));
    connect(ui->comboBoxCameraLinkMode, SIGNAL(currentIndexChanged(int)), this, SLOT(CameraSetCameraLinkMode(int)));
    connect(ui->comboBoxImageFormat, SIGNAL(currentIndexChanged(int)), this, SLOT(CameraSetImageFormat(int)));
//    connect(ui->radioButtonlive,SIGNAL(toggled(bool)),this,SLOT(CameraImageLive(bool)));
//    connect(ui->radioButtonunlive,SIGNAL(toggled(bool)),this,SLOT(CameraImageunLive(bool)));

}

OnlineTuneDialog::~OnlineTuneDialog()
{
    delete ui;
}

void OnlineTuneDialog::setCamera(G400Camera *g400_camera)
{
    m_g400_camera = g400_camera;
}


void OnlineTuneDialog::Delay_MSec(unsigned int msec)
{
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
}

void OnlineTuneDialog::onC640CameraState()
{
    int Len = g_param->controlParam.TestCameraState.length();
    char temp[Len];
    int r;
    uint32_t count = Len;
    QByteArray arr;
    for(int i = 0; i < Len; i = i + 2)
    {
        int n = i/2;
        arr[n] = g_param->controlParam.TestCameraState.mid(i,2).toInt(nullptr,16);
        temp[n] = arr.at(n);
    }
    r = uart_write(0,temp,count);
    if(r != (int)count)
    {
        qDebug()<<"TestCameraState is Error";
    }
    else
    {
        qDebug()<<"TestCameraState is ok";
    }
}

void OnlineTuneDialog::CameraSetCameraLinkMode(int state)
{
    g_param->cameraconfigParam.CameraLinkMode = state;
}

void OnlineTuneDialog::CameraSetImageFormat(int state)
{
    g_param->cameraconfigParam.ImageFormat = state;
}

//void OnlineTuneDialog::CameraImageLive(bool checked)
//{
//    if(checked == true)
//    {

//    }
//}

//void OnlineTuneDialog::CameraImageunLive(bool checked)
//{
//    if(checked == true)
//    {


//    }
//}

void OnlineTuneDialog::CameraSetImageBit(int val)
{
    g_param->cameraconfigParam.ImageBit = val;
}

void OnlineTuneDialog::CameraSetImageTap(int val)
{
    g_param->cameraconfigParam.ImageTap = val;
}


void OnlineTuneDialog::on_btnSend_clicked()
{
    if(g_param->pccontrolparam.sys_state == 0){

        if(m_g400_camera->init()){
            const uint16_t* data = reinterpret_cast<const uint16_t*>(g_param->fiberTestImage.data); // 将data指针转换为uint16_t类型
            xdma_send_start(data);
            g_param->pccontrolparam.sys_state = 1;
            ui->btnReceive->setEnabled(false);
            ui->btnSend->setText("停止发送");
        }
    }else if(g_param->pccontrolparam.sys_state == 1){


        m_g400_camera->stopsend();

        g_param->pccontrolparam.sys_state = 0;
        ui->btnReceive->setEnabled(true);
        ui->btnSend->setText("采集发送");
    }
}


void OnlineTuneDialog::on_btnReceive_clicked()
{
    if(g_param->pccontrolparam.sys_state == 0){
        g_param->camerafps = 0;
        Delay_MSec(50);
        g_param->b_showBackgroundMap = false;

        if(m_g400_camera->init()){
            m_g400_camera->starReceive();
            m_g400_camera->startCapture();
            g_param->pccontrolparam.sys_state = 2;
            ui->btnSend->setEnabled(false);
            ui->btnReceive->setText("停止接收");
        }else{

        }



    }else if(g_param->pccontrolparam.sys_state == 2){
        g_param->cameraconfigParam.CameraLive = false;
        g_param->Width = 0;
        g_param->Height = 0;
        g_param->b_showBackgroundMap = true;
        g_param->camerafps = 0;

        //m_g400_camera->stopReceive();
        m_g400_camera->close();
        g_param->pccontrolparam.sys_state = 0;
        ui->btnSend->setEnabled(true);
        ui->btnReceive->setText("数据接收");
    }
}

