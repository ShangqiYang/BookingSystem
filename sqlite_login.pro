#-------------------------------------------------
#
# Project created by QtCreator 2015-12-12T14:59:17
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sqlite_login
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    studentinfo.cpp \
    admininfo.cpp \
    addschedule.cpp \
    delete_schedule.cpp \
    changpassword.cpp

HEADERS  += login.h \
    studentinfo.h \
    admininfo.h \
    delete_schedule.h \
    addschedule.h \
    changpassword.h

FORMS    += login.ui \
    studentinfo.ui \
    admininfo.ui \
    addschedule.ui \
    delete_schedule.ui \
    changpassword.ui

RESOURCES += \
    pic.qrc

DISTFILES += \
    C:/Users/Tesla.L/Pictures/comic/dies iraed_35951.jpg
