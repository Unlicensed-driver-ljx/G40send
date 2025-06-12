#include "camerabase.h"

CameraBase::CameraBase()
{
    g_param = GlobalParameter::getInstance();
    m_bCapture = false;
}

