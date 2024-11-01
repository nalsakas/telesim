#-------------------------------------------------
#
# Project created by QtCreator 2019-12-19T09:39:18
#
#-------------------------------------------------

QT       += core gui svg xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TELESIM
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    aboutdialog.cpp \
    asvgitem.cpp \
    boxsvgitem.cpp \
    flowlayout.cpp \
    gtsvgitem.cpp \
    ksvgitem.cpp \
    linesvgitem.cpp \
        main.cpp \
        mainwindow.cpp \
    masvgitem.cpp \
    operationsdockwidget.cpp \
    railsvgitem.cpp \
    stationsdockwidget.cpp \
    logsdockwidget.cpp \
    graphicsview.cpp \
    svgitem.cpp \
    textsvgitem.cpp \
    yasvgitem.cpp \
    ystsvgitem.cpp

HEADERS += \
    aboutdialog.h \
    asvgitem.h \
    boxsvgitem.h \
    flowlayout.h \
    gtsvgitem.h \
    ksvgitem.h \
    linesvgitem.h \
        mainwindow.h \
    masvgitem.h \
    operationsdockwidget.h \
    logsdockwidget.h \
    railsvgitem.h \
    stationsdockwidget.h \
    graphicsview.h \
    svgitem.h \
    textsvgitem.h \
    yasvgitem.h \
    ystsvgitem.h

FORMS += \
        aboutdialog.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES +=

RC_ICONS = icon_.ico
