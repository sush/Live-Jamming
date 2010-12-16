# -------------------------------------------------
# Project created by QtCreator 2010-03-18T13:38:22
# -------------------------------------------------
include(../livejamming.pri)
RESOURCES = app.qrc
TARGET = livejamming_client
DESTDIR = ..
TEMPLATE = app

# FOR GUI
SOURCES += mainwindow.cpp \
    accountconnection.cpp \
    configuration_dialog.cpp \
    roomdialog.cpp \
    proxy.cpp \
    channellist.cpp \
    conversationset.cpp \
    roomplayeritem.cpp \
    channelsearch.cpp \
    audioengine.cpp \
    jackdefault.cpp \
    jackinput.cpp \
    jackoutput.cpp
HEADERS += mainwindow.h \
    accountconnection.h \
    configuration_dialog.h \
    roomdialog.h \
    proxy.h \
    channellist.h \
    conversationset.h \
    roomplayeritem.h \
    channelsearch.h \
    audioengine.h \
    jackdefault.h \
    jackinput.h \
    jackoutput.h

# OTHER
DEPENDPATH += ../../../../core
INCLUDEPATH += ../../../../core/include
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
    Packet_v1_Jam.cpp \
    Packet_v1_UserInfo.cpp \
    Channel.cpp \
    Room.cpp \
    Jam.cpp \
    Tools.cpp \
    LJ_Time.cpp \
    IComponent.cpp
HEADERS += Session.h \
    Manager.h \
    Packet.h \
    Packet_v1.h \
    PacketQueue.h \
    Bind_recv.h \
    Packet_v1_Session.h \
    Packet_v1_Channel.h \
    Packet_v1_Friend.h

# !PIERRE
DEPENDPATH += ../../../../client
INCLUDEPATH += ../../../../client/include
SOURCES += main_net.cpp \
    Client.cpp \
    ClientManager.cpp \
    Component_Session.cpp \
    Component_Friend.cpp \
    Component_Channel.cpp \
    Component_Room.cpp \
    Component_Jam.cpp \
    Component_UserInfo.cpp
HEADERS += Client.h \
    ClientManager.h \
    Component_Session.h \
    Component_Friend.h \
    Component_Channel.h \
    Component_Room.h \
    Component_Jam.h
INCLUDEPATH += ../../../../server/include
INCLUDEPATH += ../../../../include
HEADERS += Protocol.h
LIBS += -lboost_system-mt \
    -lboost_thread-mt \
    -lboost_program_options-mt
FORMS += mainwindow.ui \
    accountconnection.ui \
    configuration_dialog.ui \
    roomdialog.ui \
    newchan.ui \
    chanlist.ui \
    conversationset.ui \
    roomplayeritem.ui \
    kickdialog.ui
DEFINES += _GUI

win32 {
#use this line top compile boost.\bjam.exe --with-program_options --with-system --with-thread link=shared runtime-link=shared --layout=tagged --toolset=gcc
BOOST_DIR = D:\temp\boost
JACK_DIR = $$quote(D:\Program Files\Jack v1.9.6)
CELT_DIR = D:\temp\celt

LIBS += -lws2_32 \
        -ljack \
        -lcelt0 \
        -ljackserver \
        -L$$BOOST_DIR\stage\lib \
        -L$$CELT_DIR\celt\.libs \
        -L$$JACK_DIR\lib
INCLUDEPATH += $$BOOST_DIR \
               $$JACK_DIR\includes \
               $$CELT_DIR
QMAKE_CXXFLAGS += -D_WIN32_WINNT=0x0501
}

unix {
CONFIG += link_pkgconfig
PKGCONFIG += jack
PKGCONFIG += celt
debug:QMAKE_CXXFLAGS += -g3 \
                        -pg
}

debug:QMAKE_CXXFLAGS += -D_DEBUG
else:QMAKE_CXXFLAGS += -D_NDEBUG
