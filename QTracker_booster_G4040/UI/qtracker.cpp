#include "qtracker.h"
#include "ui_qtracker.h"
#include <QDebug>

QTracker::QTracker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QTracker)
{
    ui->setupUi(this);
    g_param = GlobalParameter::getInstance();  
//    m_tune_dialog = new OnlineTuneDialog(this);

}

QTracker::~QTracker()
{
    g_param->uart_recv_work = false;
    tcpworkerThread.quit();
    tcpworkerThread.wait();
    if(m_g400_camera != NULL)
    {
        delete m_g400_camera;
        m_g400_camera = NULL;
    }
    delete ui;
}

void QTracker::setTuneDialog(OnlineTuneDialog *tuneDialog)
{
    if(NULL != tuneDialog)
    {
       m_tune_dialog = tuneDialog;

       init();
       if(g_param->controlParam.TCPOPEN == true)
       {
           m_tcpWork = new TcpWorker;
           m_tcpWork->moveToThread(&tcpworkerThread);
           connect(this,SIGNAL(initTcpSig()),m_tcpWork,SLOT(initTcp()));
           connect(m_g400_camera,SIGNAL(SignalGrabData()),m_tcpWork,SLOT(slot_sendmessage()));
           tcpworkerThread.start();

           emit initTcpSig();
       }
    }

}

void QTracker::setCamera(G400Camera *g400_camera)
{
    m_g400_camera = g400_camera;
}

void QTracker::resizeEvent(QResizeEvent *)
{
    g_param->displayParam.imgScale.x = ui->labelImageDisplay->width() / (double)g_param->displayParam.imgSize.width;
}

void QTracker::closeEvent(QCloseEvent *)
{
    g_param->uart_recv_work = false;
    ui->labelImageDisplay->stopDisplay();
    m_tune_dialog->close();
    if(m_g400_camera != NULL)
    {
        m_g400_camera->close();
        QThread::msleep(50);
    }
    QThread::msleep(50);
    qApp->exit();
}

void QTracker::enterClose()
{
    ui->labelImageDisplay->stopDisplay();
    m_tune_dialog->close();
    if(m_g400_camera != NULL)
    {
        m_g400_camera->close();
    }
    QThread::msleep(50);
    qApp->exit();
}

void QTracker::keyPressEvent(QKeyEvent *event)
{
    ///ESC
    if(event->key() == Qt::Key_Escape)
    {
        m_tune_dialog->show(); /// 20190723 wangzy
    }

}

void QTracker::init()
{
    int disp_fps = (int)(1000.0f / (g_param->displayParam.fps + 0.00000001));
    if(disp_fps < 33)
    {
        disp_fps = 33;
    }
    ui->labelImageDisplay->startDisplay(/*disp_fps*/1000);
    ui->labelImageDisplay->updateImage(g_param->imageDisplay);
}


