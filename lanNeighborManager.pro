#-------------------------------------------------
#
# Project created by QtCreator 2022-10-02T17:41:22
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lanNeighborManager
TEMPLATE = app

TRANSLATIONS += language_zh.ts \
                language_en.ts

SOURCES += main.cpp\
        mainwnd.cpp \
    localhost.cpp \
    neighborhostwidget.cpp \
    neighborhoststackpage.cpp \
    neighboruserlabel.cpp \
    setuserdlg.cpp

HEADERS  += mainwnd.h \
    localhost.h \
    neighborhostwidget.h \
    neighborhoststackpage.h \
    neighboruserlabel.h \
    setuserdlg.h

FORMS    += mainwnd.ui \
    neighborhostwidget.ui \
    neighborhoststackpage.ui \
    neighboruserlabel.ui \
    setuserdlg.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    languages/language_en.ts \
    languages/language_zh.ts
