#-------------------------------------------------
#
# Project created by QtCreator 2014-02-04T16:29:06
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QGpa
TEMPLATE = app


SOURCES += main.cpp \
    classes/checkcodedlg.cpp \
    classes/qgpa.cpp \
    classes/queryresult.cpp \
    classes/session.cpp

HEADERS  += \
    encrypt.h \
    classes/checkcodedlg.h \
    classes/qgpa.h \
    classes/queryresult.h \
    classes/session.h

FORMS    += \
    ui/checkcodedlg.ui \
    ui/qgpa.ui \
    ui/queryresult.ui

RESOURCES += \
    qgpa.qrc

RC_FILE += qgpa.rc

OTHER_FILES += \
    qgpa.rc
