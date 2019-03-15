x#-------------------------------------------------
#
# Project created by QtCreator 2019-02-27T10:23:14
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = picadvisor
TEMPLATE = app


SOURCES += main.cpp \
    frmlogin.cpp \
    database.cpp \
    error.cpp \
    user.cpp \
    frmmainmenu.cpp \
    frmstartgame.cpp \
    highscore.cpp \
    level.cpp

HEADERS  += \
    frmlogin.h \
    database.h \
    error.h \
    user.h \
    databaseanswer.h \
    frmmainmenu.h \
    frmstartgame.h \
    level.h \
    highscore.h

FORMS    += \
    frmlogin.ui \
    frmmainmenu.ui \
    frmstartgame.ui
