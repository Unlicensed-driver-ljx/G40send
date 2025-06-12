#include "tcpworker.h"

void TcpWorker::initTcp()
{
    //Send_tmp = new char[1920*1080*3];
    Send_tmp = new char[1920*1080];
    TCP_server = new QTcpServer();
    TCP_connectSocket = nullptr;
    m_globalparameter=GlobalParameter::getInstance();
    if (TCP_server->listen(QHostAddress::Any, m_globalparameter->controlParam.m_TCPTuPort))
     { connect(TCP_server, &QTcpServer::newConnection, this, &TcpWorker::slot_newconnect);

        qDebug()<< "TCP server Listen is OK";
    }
    else
    {
       qDebug()<< "TCP network send open error";
    }
}

void TcpWorker::slot_newconnect()
{
    if (TCP_server->hasPendingConnections())  //
    {
        TCP_connectSocket = TCP_server->nextPendingConnection(); //
        qDebug()<<("client login!"); //
        connect(TCP_connectSocket, SIGNAL(readyRead()), this, SLOT(slot_recvmessage()));
        m_bSendTcp = true;
    }
}
void TcpWorker::slot_recvmessage()
{
    if (TCP_connectSocket != nullptr)
    {
        QByteArray array = TCP_connectSocket->readAll();
        if(array.data()[0] == 'c')
        {
            m_bSendTcp = false;
            qDebug()<<"AAAA recv tcp Message";
            QTimer::singleShot(1000,this,&TcpWorker::slot_disconnect);
        }
    }
}

void TcpWorker::slot_disconnect()
{
     qDebug()<<"AAAA disconnect is enter";
    if (TCP_connectSocket != nullptr)
    {
        TCP_connectSocket->close();
        TCP_connectSocket->deleteLater();
        TCP_connectSocket=nullptr;
    }
}


void TcpWorker::slot_sendmessage()
{
    if( false == m_bSendTcp)
        return;
    if (TCP_connectSocket != nullptr)
    {
        skip_count++;
        if(skip_count >= m_globalparameter->adjFps){
            memcpy(Send_tmp,m_globalparameter->framebuffer,1920*1080);
           // SendMat=cv::Mat(1080,1920,CV_8UC3,Send_tmp);
             SendMat=cv::Mat(1920,1080,CV_8UC1,Send_tmp);
            QByteArray arrayKK;
            arrayKK.resize(1920*1080*1);//
           // memcpy(arrayKK.data(),SendMat.data, 1920*1080*3);//
             memcpy(arrayKK.data(),SendMat.data,1920*1080);
            TCP_connectSocket->write(QString("size=%1").arg(1920*1080).toLocal8Bit());
            //TCP_connectSocket->write(QString("size=%1").arg(1920*1080*3).toLocal8Bit());
            if (TCP_connectSocket == nullptr)
                return;
            TCP_connectSocket->waitForReadyRead();
            TCP_connectSocket->write(arrayKK);   //
            if (TCP_connectSocket == nullptr)
                return;
            TCP_connectSocket->waitForReadyRead();
            skip_count=0;
        }
    }
}
