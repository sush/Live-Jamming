# -------------------------------------------------
# Project created by QtCreator 2010-03-18T13:38:22
# -------------------------------------------------
TARGET = livejammin_client
TEMPLATE = app
SOURCES += mainwindow.cpp \
    accountconnection.cpp \
    configuration_dialog.cpp \
    roomdialog.cpp \
    parameters.cpp \
    proxy.cpp \
    nespaudio.cpp \
    channellist.cpp \
    conversationset.cpp
HEADERS += mainwindow.h \
    accountconnection.h \
    configuration_dialog.h \
    roomdialog.h \
    parameters.h \
    proxy.h \
    nespaudio.h \
    channellist.h \
    conversationset.h
DEPENDPATH += ../../core
INCLUDEPATH += ../../core/include
SOURCES += Manager.cpp \
    Session.cpp \
    Bind_recv.cpp \
    Request.cpp \
    PacketQueue.cpp \
    Packet.cpp \
    Packet_v1.cpp \
    Packet_v1_Session.cpp \
    Packet_v1_Channel.cpp \
    Packet_v1_Friend.cpp \
    Packet_v1_Room.cpp \
    Channel.cpp \
    Room.cpp
HEADERS += Session.h \
    Manager.h \
    Packet.h \
    Packet_v1.h \
    PacketQueue.h \
    Bind_recv.h \
    Packet_v1_Session.h \
    Packet_v1_Channel.h \
    Packet_v1_Friend.h
DEPENDPATH += ../../client
INCLUDEPATH += ../../client/include
INCLUDEPATH += /usr/include/qt4/QtMultimedia
INCLUDEPATH += /usr/include/qt4
SOURCES += main_net.cpp \
    Client.cpp \
    ClientManager.cpp \
    Component_Session.cpp \
    Component_Friend.cpp \
    Component_Channel.cpp \
    Component_Room.cpp
HEADERS += Audio.h \
    Client.h \
    ClientManager.h \
    Component_Session.h \
    Component_Friend.h \
    Component_Channel.h
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
    -L../../libs\
    -L/usr/share/qt4/lib
FORMS += mainwindow.ui \
    accountconnection.ui \
    configuration_dialog.ui \
    roomdialog.ui \
    newchan.ui \
    convset.ui \
    chanlist.ui \
    conversationset.ui
DEFINES += _GUI
debug:QMAKE_CXXFLAGS += -D_DEBUG \
    -g3 \
    -pg
else:QMAKE_CXXFLAGS += -D_NDEBUG
QT += multimedia
