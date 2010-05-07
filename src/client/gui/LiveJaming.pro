# -------------------------------------------------
# Project created by QtCreator 2010-03-18T13:38:22
# -------------------------------------------------
QT += network
TARGET = LiveJaming
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    accountconnection.cpp \
    configuration_dialog.cpp \
    roomdialog.cpp \
    network.cpp \
    parameters.cpp
HEADERS += mainwindow.h \
    accountconnection.h \
    configuration_dialog.h \
    roomdialog.h \
    network.h \
    parameters.h

DEPENDPATH += ../../client
INCLUDEPATH += ../../client/include
SOURCES += Client.cpp\
    ClientManager.cpp \
    Component_Session.cpp
HEADERS += Audio.h \
    Client.h \
    ClientManager.h \
    Component_Session.h

DEPENDPATH += ../../core
INCLUDEPATH += ../../core/include
SOURCES += Packet.cpp \
    Packet_v1.cpp \
    PacketQueue \
    Packet_v1_Session_AuthRequest.cpp
INCLUDEPATH += ../../../src/include
HEADERS += boost/threadpool.hpp
INCLUDEPATH += ../../../src/server/include
HEADERS += Config.h

FORMS += mainwindow.ui \
    accountconnection.ui \
    configuration_dialog.ui \
    roomdialog.ui
CONFIG += link_pkgconfig
PKGCONFIG += yaml-cpp
