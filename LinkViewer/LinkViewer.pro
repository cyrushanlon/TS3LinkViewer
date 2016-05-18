#-------------------------------------------------
#
# Project created by QtCreator 2016-05-15T19:51:04
#
#-------------------------------------------------

QT       += core gui webenginewidgets webengine

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TS3LinkViewer
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp \
    settingsdialog.cpp \
    settingsmanager.cpp

HEADERS  += widget.h \
    settingsdialog.h \
    settingsmanager.h

FORMS    += widget.ui \
    settingsdialog.ui

WEBENGINE_CONFIG += use_proprietary_codecs

include(./QHotkey/qhotkey.pri)
