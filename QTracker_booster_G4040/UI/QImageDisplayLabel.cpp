#include "QImageDisplayLabel.h"

QImageDisplayLabel::QImageDisplayLabel(QWidget *parent)
	: QLabel(parent)
{
	ui.setupUi(this);
    g_param = GlobalParameter::getInstance();
    image_1.load("../CAMERACONTROL/OR4040FSI.png");
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimerDisplay()));
}

QImageDisplayLabel::~QImageDisplayLabel()
{
	stopDisplay();
}

void QImageDisplayLabel::startDisplay(int ms /*= 40*/)
{
	m_timer.stop();
	m_timer.start(ms);
}

void QImageDisplayLabel::stopDisplay()
{
	m_timer.stop();
}

QImage QImageDisplayLabel::MatToQImage(Mat& mat)
{
    cv::Mat rgb;
    cv::cvtColor(mat, rgb, cv::COLOR_BGR2RGB);  // 将BGR格式转换为RGB格式
    QImage img((const unsigned char*)rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
    return img.copy();  // 拷贝数据，避免内存问题
}

void QImageDisplayLabel::updateImage(Mat frame)
{
	if (frame.channels() == 3)
	{
		try
        {
            m_qimage = MatToQImage(frame);
		}
		catch (cv::Exception* e)
		{
            qDebug() << "QImageDisplayLabel::updateImage exception " << e->what();
		}
	} 
	else
    {
        if(!frame.empty())
            m_qimage = MatToQImage(frame);
    }

    if (!m_qimage.isNull()&&g_param->b_showBackgroundMap == false&&g_param->EstimateGather == true)
    {
        if(g_param->show == true)
        {
            OverlayCharacter();
            this->setPixmap(QPixmap::fromImage(m_qimage));
        }
        else
        {
            g_param->camerafps = 0;
            m_qimage = image_1;
            OverlayCharacter();
            this->setPixmap(QPixmap::fromImage(m_qimage));
            this->setAttribute(Qt::WA_TranslucentBackground);
            this->show();
        }
	} 
	else
    {
        m_qimage = image_1;
        OverlayCharacter();
        this->setPixmap(QPixmap::fromImage(m_qimage));
        this->setAttribute(Qt::WA_TranslucentBackground);
        this->show();
    }
}

void QImageDisplayLabel::OverlayCharacter()
{
    m_painter.begin(&m_qimage);
    m_pen.setWidth(2);
    m_pen.setColor(Qt::green);
    m_painter.setPen(m_pen);
    m_pen.setWidth(1);
    m_font.setPointSize(10.5);
    m_pen.setColor(Qt::green);
    m_painter.setPen(m_pen);
    m_painter.setFont(m_font);
    m_painter.setPen(m_pen);
    QString info_1 = QString(" FPS %1")\
            .arg(QString("%1").arg(g_param->camerafps,4,'f',2,QLatin1Char('0')));
    m_painter.drawText(m_qimage.rect(),Qt::AlignLeft|Qt::AlignTop,info_1);

    m_painter.end();
}

void QImageDisplayLabel::onTimerDisplay()
{
    updateImage(g_param->imageDisplay);
}

void QImageDisplayLabel::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton )
	{
        int x = (int)((float)event->pos().x() / g_param->displayParam.imgScale.x);
        int y = (int)((float)event->pos().y() / g_param->displayParam.imgScale.y);
	}
}

void QImageDisplayLabel::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0)
    {
        if((g_param->focusParam.image_w>20)&&(g_param->focusParam.image_h>20))
        {
            g_param->focusParam.image_w = g_param->focusParam.image_w - 10;
            g_param->focusParam.image_h = g_param->focusParam.image_h - 10;
        }
        if((g_param->focusParam.image_w<=10)&&(g_param->focusParam.image_h<=10))
        {
            g_param->focusParam.image_w = 10;
            g_param->focusParam.image_h = 10;
        }

    }
    else
    {
        if((g_param->focusParam.image_w<500)&&(g_param->focusParam.image_h<500))
        {
            g_param->focusParam.image_w = g_param->focusParam.image_w + 10;
            g_param->focusParam.image_h = g_param->focusParam.image_h + 10;
        }
        if((g_param->focusParam.image_w>=500)&&(g_param->focusParam.image_h>=500))
        {
            g_param->focusParam.image_w = 500;
            g_param->focusParam.image_h = 500;
        }
    }
}


void QImageDisplayLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    g_param->displayParam.imgScale.x = width() / (double)g_param->displayParam.imgSize.width;
    g_param->displayParam.imgScale.y = height() / (double)g_param->displayParam.imgSize.height;

	if (event->button() == Qt::LeftButton)
    {
        g_param->focusParam.mouseDoubleClick = true;
        int x = (int)((float)event->pos().x() / g_param->displayParam.imgScale.x);
        int y = (int)((float)event->pos().y() / g_param->displayParam.imgScale.y);
	}
}

