#ifndef TCPWORKER_H
#define TCPWORKER_H

#include "opencv2/opencv.hpp"
#include "Tool/GlobalParameter.h"
#include "Camera/g400camera.h"

#include <QMainWindow>
#include <QList>
#include <QMessageBox>
#include <iostream>
#include <QCloseEvent>
#include <QDateTime>
#include <QTimer>
#include <QtMath>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtConcurrent/QtConcurrent>
#include <QScreen>
#include <QDesktopWidget>
#include <QApplication>
#include <QRect>
#include <QtConcurrent>
#include <QFuture>

class TcpWorker : public QObject
{
    Q_OBJECT

public slots:
    void initTcp();
    void slot_newconnect();
    void slot_sendmessage();
    void slot_recvmessage(); //
    void slot_disconnect(); //

signals:
    void resultReady(const QString &result);

private:
    QTcpServer* TCP_server; //QTcpServer
    QTcpSocket* TCP_connectSocket;
    bool m_bSendTcp= false;
    int skip_count = 0;
    int adjFps = 10;
    char *Send_tmp;
    cv::Mat SendMat;
    GlobalParameter* m_globalparameter;
};

#endif // TCPWORKER_H
