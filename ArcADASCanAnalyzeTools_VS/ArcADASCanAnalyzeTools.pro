QT       += core gui
QT       += concurrent
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
#CONFIG += console

DESTDIR=dest
OBJECTS_DIR=obj
MOC_DIR=moc

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_MESSAGELOGCONTEXT

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32-msvc*:QMAKE_CXXFLAGS += /utf-8

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_CXXFLAGS_RELEASE = -Od -ZI -MD
QMAKE_LFLAGS_RELEASE = /DEBUG /INCREMENTAL:NO

# 方便生成DUMP调试
LIBS += -lDbgHelp

SOURCES += \
    MyLabel.cpp \
    TipsLabel.cpp \
    canparser.cpp \
    main.cpp \
    Widget.cpp

HEADERS += \
    ControlCAN.h \
    MyLabel.h \
    TipsLabel.h \
    Widget.h \
    canparser.h \
    global_header.h \
    threadsafe_queue.inl

FORMS += \
    Widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += "$$PWD/thirdparty/controlcan"
win32: LIBS += -Wl,--enable-stdcall-fixup -L$$PWD/thirdparty/controlcan -lControlCAN

INCLUDEPATH += "$$PWD/thirdparty/dpcppp/include"
win32: LIBS += -L$$PWD/thirdparty/dpcppp/lib -llibdbcppp

#图标
RC_ICONS = favicon.ico
#版本号
VERSION = 1.301.5306.3
#中文
RC_LANG = 0x0004
# 公司名
QMAKE_TARGET_COMPANY = "ArcSoft Corporation Limited"
# 产品名称
QMAKE_TARGET_PRODUCT = "ArcCanAnalyseTool"
# 详细描述
QMAKE_TARGET_DESCRIPTION = "CAN Analyse Tool"
# 版权
QMAKE_TARGET_COPYRIGHT = "Copyright 2021 ArcSoft Corporation Limited. All rights reserved."

RESOURCES += \
    app.qrc
