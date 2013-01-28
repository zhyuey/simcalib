#-------------------------------------------------
#
# Project created by QtCreator 2013-01-22T13:03:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_cv_calib
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calibratethread.cpp \
    imagingwindow.cpp

HEADERS  += mainwindow.h \
    calibratethread.h \
    imagingwindow.h



FORMS    += mainwindow.ui

INCLUDEPATH += d:/opencv/build/include/
CONFIG(release,debug|release){
    LIBS += D:\\opencv\\build\\x86\\vc10\\lib\\opencv_core231.lib \
            D:\\opencv\\build\\x86\\vc10\\lib\\opencv_imgproc231.lib \
            D:\\opencv\\build\\x86\\vc10\\lib\\opencv_highgui231.lib \
            D:\\opencv\\build\\x86\\vc10\\lib\\opencv_calib3d231.lib \
            D:\\opencv\\build\\x86\\vc10\\lib\\opencv_features2d231.lib \

}
CONFIG(debug,debug|release){
    LIBS += D:\\opencv\\build\\x86\\vc10\\lib\\opencv_core231d.lib \
            D:\\opencv\\build\\x86\\vc10\\lib\\opencv_imgproc231d.lib \
            D:\\opencv\\build\\x86\\vc10\\lib\\opencv_highgui231d.lib \
            D:\\opencv\\build\\x86\\vc10\\lib\\opencv_calib3d231d.lib \
            D:\\opencv\\build\\x86\\vc10\\lib\\opencv_features2d231d.lib \
}


RC_FILE += app.rc
