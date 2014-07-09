#-------------------------------------------------
#
# Project created by QtCreator 2014-02-04T16:29:06
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QGpa
TEMPLATE = app


SOURCES += main.cpp\
        qgpa.cpp \
    checkcodedlg.cpp \
    session.cpp

HEADERS  += qgpa.h \
    checkcodedlg.h \
    local.h \
    session.h \
    ui_checkcodedlg.h

FORMS    += qgpa.ui \
    checkcodedlg.ui

RESOURCES += \
    qgpa.qrc
