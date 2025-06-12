#include "ecotracker.h"

ECOTracker::ECOTracker()
{
    m_bInit = false;

    m_kcf = new kcf::KCFTracker(true, true, false, true);

}

void ECOTracker::reset()
{
    m_bInit = false;
}

void ECOTracker::init(Mat &im, const Rect2f &rect, const eco::EcoParameters &paramters)
{
    if(m_bInit == false)
    {
        m_init_frame = im;
        m_init_box = rect;
        m_init_parameters = paramters;
        this->start();

        m_kcf->init(m_init_frame, m_init_box);
    }
    else
    {
        cout << "ECOTracker::init already done" << endl;
    }
}

float ECOTracker::getScore()
{
    if(m_bInit == false)
    {
        return m_kcf->getPeakValue();
    }
    else
    {
        return m_eco.getScore();
    }
}

Rect2f ECOTracker::update(const Mat &frame)
{
    if(m_bInit == false)
    {
        return m_kcf->update(frame);
    }
    else
    {
        m_eco.update(frame, m_roi);
        return m_roi;
    }
}

void ECOTracker::run()
{
    if(m_bInit == false)
    {
        m_eco.init(m_init_frame, m_init_box, m_init_parameters);
        m_bInit = true;
    }
    else
    {
        cout << "ECOTracker::run m_bInit == true" << endl;
    }
}

