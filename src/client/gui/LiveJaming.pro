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
DEPENDPATH += ../../core
INCLUDEPATH += ../../core/include
SOURCES += Session.cpp \
    Manager.cpp \
    Packet.cpp \
    Packet_v1.cpp \
    PacketQueue.cpp \
    Packet_v1_Session_AuthRequest.cpp \
    Bind_recv.cpp
HEADERS += Session.h \
    Manager.h \
    Packet.h \
    Packet_v1.h \
    PacketQueue.h \
    Packet_v1_Session_AuthRequest.h \
    Bind_recv.h
DEPENDPATH += ../../client
INCLUDEPATH += ../../client/include
SOURCES += Client.cpp \
    ClientManager.cpp \
    Component_Session.cpp
HEADERS += Audio.h \
    Client.h \
    ClientManager.h \
    Component_Session.h
INCLUDEPATH += ../../include/boost
HEADERS += threadpool.hpp
INCLUDEPATH += ../../server/include
HEADERS += Config.h
INCLUDEPATH += ../../include
HEADERS += Protocol.h
LIBS += -lboost_system \
    -lboost_thread-mt \
    -lboost_program_options \
    -lyaml-cpp \
    -lmysqlpp
FORMS += mainwindow.ui \
    accountconnection.ui \
    configuration_dialog.ui \
    roomdialog.ui \
    newchan.ui
CONFIG += link_pkgconfig
PKGCONFIG += yaml-cpp
