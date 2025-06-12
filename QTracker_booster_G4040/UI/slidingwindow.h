#ifndef SLIDINGWINDOW_H
#define SLIDINGWINDOW_H

#include <QWidget>
#include <QSplitter>
#include <QPushButton>
#include <QDesktopWidget>
#include <QMouseEvent>
#include "qtracker.h"
#include "onlinetunedialog.h"
#include "Camera/g400camera.h"
#include <QApplication>


class SlidingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SlidingWindow(QWidget *parent = 0);
    ~SlidingWindow();

protected:
void resizeEvent(QResizeEvent *event);
void keyPressEvent(QKeyEvent *event);
void keyReleaseEvent(QKeyEvent *event);
//bool eventFilter(QObject *obj, QEvent *event);
private:
void setBtnPos();
void setBtnIcon();
private slots:
void slotClickedBtn();
void slotSplitterMoved(int pos, int index);

private:
QPoint dragPosition;
QSplitter *splitter;
QFrame *contentFrame;
QFrame *listFrame;
//QPushButton *pushButton;

//QIcon leftIcon;
//QIcon rightIcon;

G400Camera*         m_g400_camera;
QTracker*           m_leftTrack;
OnlineTuneDialog*   m_rightTuneDialog;

bool m_bTuneShow;
};

#endif // SLIDINGWINDOW_H
