#-------------------------------------------------
#
# Project created by QtCreator 2019-07-17T14:02:10
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += network
QT       += concurrent
#QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTracker_booster
TEMPLATE = app
CONFIG += c++11

QMAKE_CFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO

SOURCES += UI/main.cpp \
    Camera/kfifo.cpp \
    Camera/xdma.cpp \
    Camera/xdma_app.cpp \
    IO/tcpworker.cpp \
    UI/qtracker.cpp \
    Camera/camerabase.cpp \
    Tool/GlobalParameter.cpp \
    UI/slidingwindow.cpp \
    UI/QImageDisplayLabel.cpp \
    UI/onlinetunedialog.cpp \
    Camera/g400camera.cpp

HEADERS  += UI/qtracker.h \
    Camera/kfifo.h \
    Camera/xdma.h \
    Camera/xdma_app.h \
    Camera/camerabase.h \
    IO/tcpworker.h \
    Tool/DataCacheQueue.h \
    Tool/GlobalParameter.h \
    UI/slidingwindow.h \
    UI/QImageDisplayLabel.h \
    UI/onlinetunedialog.h \
    Camera/g400camera.h

FORMS    += UI/qtracker.ui \
    UI/QImageDisplayLabel.ui \
    UI/onlinetunedialog.ui

INCLUDEPATH +=  ../include  \
                /usr/include  \
                /usr/include/opencv4 \
                /usr/include/opencv4/opencv2   \
                /usr/include/opencv4/opencv2/tracking   \
                /usr/local/cuda-11/include \
                /home/orangepi/debug/xdma_app_1.0.3-1.0

LIBS += /usr/lib/aarch64-linux-gnu/libopencv_video.so  \
        /usr/lib/aarch64-linux-gnu/libopencv_objdetect.so \
        /usr/lib/aarch64-linux-gnu/libopencv_ml.so  \
        /usr/lib/aarch64-linux-gnu/libopencv_core.so \
        /usr/lib/aarch64-linux-gnu/libopencv_features2d.so  \
        /usr/lib/aarch64-linux-gnu/libopencv_imgproc.so \
        /usr/lib/aarch64-linux-gnu/libopencv_highgui.so \
        /usr/lib/aarch64-linux-gnu/libopencv_flann.so   \
        /usr/lib/aarch64-linux-gnu/libopencv_calib3d.so   \
        /usr/lib/aarch64-linux-gnu/libopencv_videoio.so   \
        /usr/lib/aarch64-linux-gnu/libopencv_video.so   \
        /usr/lib/aarch64-linux-gnu/libopencv_videostab.so   \
        /usr/lib/aarch64-linux-gnu/libopencv_dnn.so   \
        /usr/lib/aarch64-linux-gnu/libopencv_imgcodecs.so   \
        /usr/lib/aarch64-linux-gnu/libopencv_*

RESOURCES +=
