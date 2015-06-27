#-------------------------------------------------
#
# Project created by QtCreator 2015-02-14T20:59:51
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlaneTest
TEMPLATE = app

#INCLUDEPATH += F:/Win_32bit/gdal/Release/include
#LIBS += F:/Win_32bit/gdal/Release/lib/gdal_i.lib


SOURCES += main.cpp\
        mainwindow.cpp \
    myrectf.cpp \
    drawobject.cpp \
    paintarea.cpp \
    mypolygon.cpp \
    datadefine.cpp \
    eagleeyemap.cpp \
    detailedmap.cpp \
    geoshapedata.cpp \
    maptool.cpp \
    udpsettingdialog.cpp \
    udpmsgformat.cpp \
    coordtranslate.cpp \
    indicatingmsgwidget.cpp \
    indicateheadingwidget.cpp \
    uiparamconfig.cpp

HEADERS  += mainwindow.h \
    myrectf.h \
    drawobject.h \
    paintarea.h \
    mypolygon.h \
    datadefine.h \
    eagleeyemap.h \
    detailedmap.h \
    geoshapedata.h \
    maptool.h \
    udpsettingdialog.h \
    udpmsgformat.h \
    coordtranslate.h \
    indicatingmsgwidget.h \
    indicateheadingwidget.h \
    uiparamconfig.h

FORMS    += mainwindow.ui \
    udpsettingdialog.ui \
    udpmsgformat.ui
