#pragma once

#include <QLabel>
#include <QTimer>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <QPixmap>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QFont>
#include <QPen>
#include <QDebug>
#include <QApplication>
#include <qdesktopwidget.h>
#include "ui_QImageDisplayLabel.h"
#include "Tool/GlobalParameter.h"

/**
* @brief 基于QLabel设计的图像显示控件类。
* @date 2018/03/06
* @version 1.1
* @author Wangzy
*/
class QImageDisplayLabel : public QLabel
{
	Q_OBJECT

public:
	
	QImageDisplayLabel(QWidget *parent = Q_NULLPTR);
	~QImageDisplayLabel();
	void startDisplay(int ms = 40);
	void stopDisplay();
	void updateImage(Mat frame);
    void OverlayCharacter();
    QImage MatToQImage(Mat& mat);

public slots:
	void onTimerDisplay();
protected:
    void mousePressEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
private:
	Ui::QImageDisplayLabel ui;

    QTimer m_timer;
    GlobalParameter* g_param;
	Mat m_rgbFrame;
    QImage m_qimage;
    QImage m_qimageScale;
    QPainter m_painter;
    QFont m_font;
	QPen m_pen;
    QImage image_1;

};
