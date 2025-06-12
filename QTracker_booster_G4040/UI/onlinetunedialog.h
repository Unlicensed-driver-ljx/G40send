#ifndef ONLINETUNEDIALOG_H
#define ONLINETUNEDIALOG_H

#include <QDialog>
#include <QDir>
#include <QFile>
#include <QTimer>
#include "Tool/GlobalParameter.h"
#include "Camera/g400camera.h"
#include <QtConcurrent>
#include <QThread>
//#include <QtCharts/QChart>
//#include <QtCharts/QValueAxis>
//#include <QtCharts/QChartView>
//#include <QtCharts/QLineSeries>
//#include <QChartView>
//#include <QBarSet>
//#include <QBarSeries>
//#include <QBarCategoryAxis>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>

//QT_CHARTS_USE_NAMESPACE

namespace Ui {
class OnlineTuneDialog;
}

class OnlineTuneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OnlineTuneDialog(QWidget *parent = 0);
    ~OnlineTuneDialog();

    void setCamera(G400Camera* g400_camera);
public slots:

    void Delay_MSec(unsigned int msec);

    void CameraSetCameraLinkMode(int state);
    void CameraSetImageFormat(int state);
//    void CameraImageLive(bool checked);
//    void CameraImageunLive(bool checked);
    void CameraSetImageBit(int val);
    void CameraSetImageTap(int val);
    void onC640CameraState();

private slots:
    void on_btnSend_clicked();

    void on_btnReceive_clicked();

private:
    Ui::OnlineTuneDialog *ui;
    GlobalParameter* g_param;
    G400Camera* m_g400_camera;
};

#endif // ONLINETUNEDIALOG_H
