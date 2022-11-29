QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4):

QT += widgets multimedia multimediawidgets gui network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arr.cpp \
    arrs.cpp \
    main.cpp \
    mainwindow.cpp \
    myslider.cpp \
    opencvui.cpp \
    target.cpp

HEADERS += \
    arr.h \
    arrs.h \
    mainwindow.h \
    myslider.h \
    opencvui.h \
    target.h

FORMS += \
    mainwindow.ui \
    opencvui.ui

TRANSLATIONS += \
    BurstPointDetection_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc


INCLUDEPATH += $$PWD/OpenCV-MinGW-Build-OpenCV-4.5.2-x64/include
INCLUDEPATH += $$PWD/OpenCV-MinGW-Build-OpenCV-4.5.2-x64/include/opencv2

LIBS += $$PWD/OpenCV-MinGW-Build-OpenCV-4.5.2-x64/x64/mingw/bin/libopencv_*.dll

