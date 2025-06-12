#ifndef ECOTRACKER_H
#define ECOTRACKER_H

#include <QThread>
#include <iostream>
#include "eco.hpp"
#include "Track/KCF_faro/src/kcftracker.hpp"

using namespace std;

class ECOTracker : public QThread
{
public:
    ECOTracker();
    void reset();
    void init(cv::Mat &im, const cv::Rect2f &rect, const eco::EcoParameters &paramters);
    cv::Rect2f update(const cv::Mat &frame);
    float getScore();

protected:
    void run();

private:
    eco::ECO m_eco;

    kcf::KCFTracker* m_kcf;

    bool m_bInit;
    Mat m_init_frame;
    Rect2f m_init_box;
    eco::EcoParameters m_init_parameters;
    Rect2f m_roi;
};

#endif // ECOTRACKER_H
