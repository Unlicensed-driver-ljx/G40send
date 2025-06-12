#ifndef CAMERABASE_H
#define CAMERABASE_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "Tool/GlobalParameter.h"

/**
 * @brief The CameraBase class
 */

class CameraBase : public QThread
{
public:
    CameraBase();
    /// init
    virtual bool init() = 0;
    /// close
    virtual void close() = 0;
    /// start capture image
    virtual void startCapture() = 0;
    /// stop capture image
    virtual void stopCapture() = 0;
    /// read frame
    virtual bool readCurrentFrame() = 0;
protected:
    /// true: capture image, false: idle
    bool m_bCapture;

    GlobalParameter* g_param;
};

#endif // CAMERABASE_H
