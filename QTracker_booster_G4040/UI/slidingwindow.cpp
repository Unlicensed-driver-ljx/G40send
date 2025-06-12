#include "slidingwindow.h"
#include <QDebug>
SlidingWindow::SlidingWindow(QWidget *parent) :
    QWidget(parent),m_bTuneShow(true)
{
    resize(1365,1000);
    splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setHandleWidth(1);
    splitter->setStyleSheet("QSplitter::handle{background:#FFFFFF}");

    m_g400_camera = new G400Camera();

    m_leftTrack = new QTracker(this);
    m_leftTrack->setCamera(m_g400_camera);
    splitter->addWidget(m_leftTrack);

    m_rightTuneDialog = new OnlineTuneDialog(this);
    m_rightTuneDialog->setCamera(m_g400_camera);
    splitter->addWidget(m_rightTuneDialog);
//    pushButton = new QPushButton(this);
//    pushButton->setFocusPolicy(Qt::NoFocus);
//    pushButton->hide();
//    pushButton->setFixedSize(13, 42);
//    pushButton->setIconSize(pushButton->size());
//    pushButton->setStyleSheet("background:#00FF00");
//    pushButton->setIcon(rightIcon);
//    pushButton->move(m_leftTrack->width() - pushButton->width()-2, (m_leftTrack->height() - pushButton->height())/2);

    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,1);

    m_leftTrack->setTuneDialog(m_rightTuneDialog);

    QList <int> sizeList;
    sizeList.append(1200);
    sizeList.append(160);
    splitter->setSizes(sizeList);
    setBtnIcon();
}

SlidingWindow::~SlidingWindow()
{
    m_leftTrack->enterClose();
}

void SlidingWindow::resizeEvent(QResizeEvent *event)
{
    splitter->setGeometry(0, 0, width(), height());
    move((QApplication::desktop()->width() - width())/2,  (QApplication::desktop()->height() - height())/2);
    QWidget::resizeEvent(event);
}

void SlidingWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        qDebug()<<"Escape is down";
    }
}

void SlidingWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        //m_leftTrack->keyReleaseMM(event);
    }
}


void SlidingWindow::setBtnPos()
{
//    pushButton->move(m_leftTrack->width() - pushButton->width(), (m_leftTrack->height() - pushButton->height())/2);
}

void SlidingWindow::setBtnIcon()
{
//    if (m_leftTrack->width() != 0) {
//    pushButton->setIcon(rightIcon);
//    }
//    else {
//    pushButton->setIcon(leftIcon);
//    }
}
void SlidingWindow::slotClickedBtn()
{
    QList <int> sizeList;
    sizeList.clear();
    if (m_bTuneShow)
    {
        sizeList.append(1040);
        sizeList.append(0);
        m_bTuneShow = false;
    }
    else
    {
        sizeList.append(730);
        sizeList.append(310);
        m_bTuneShow = true;
    }
    splitter->setSizes(sizeList);
}
void SlidingWindow::slotSplitterMoved(int pos, int index)
{
    Q_UNUSED(pos)
    Q_UNUSED(index)
//    setBtnIcon();
//    setBtnPos();
}

