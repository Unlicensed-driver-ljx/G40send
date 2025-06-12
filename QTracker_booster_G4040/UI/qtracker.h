#ifndef QTRACKER_H
#define QTRACKER_H

#include <QMainWindow>
#include <QtCore>
#include "Camera/g400camera.h"
#include "UI/onlinetunedialog.h"
#include "Tool/GlobalParameter.h"
#include "IO/tcpworker.h"

namespace Ui {
class QTracker;
}
class QTracker : public QMainWindow
{
    Q_OBJECT

public:
    explicit QTracker(QWidget *parent = 0);
    void setTuneDialog(OnlineTuneDialog* tuneDialog);
    void setCamera(G400Camera* g400_camera);
    void enterClose();
    ~QTracker();



protected:
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *event);
//    void paintEvent(QPaintEvent *event);

public slots:
    void init();
signals:
    void initTcpSig();
private:
    Ui::QTracker *ui;
    OnlineTuneDialog* m_tune_dialog;
    GlobalParameter* g_param;

    G400Camera* m_g400_camera;

    TcpWorker* m_tcpWork;
    QThread tcpworkerThread;

};

#endif // QTRACKER_H
