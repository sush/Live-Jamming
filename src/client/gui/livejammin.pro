# -------------------------------------------------
# Project created by QtCreator 2010-03-18T13:38:22
# -------------------------------------------------
TARGET = livejammin_client
TEMPLATE = app
SOURCES += mainwindow.cpp \
    accountconnection.cpp \
    configuration_dialog.cpp \
    roomdialog.cpp \
    parameters.cpp
HEADERS += mainwindow.h \
    accountconnection.h \
    configuration_dialog.h \
    roomdialog.h \
    parameters.h \
    convset.h
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
    Channel.cpp
HEADERS += Session.h \
    Manager.h \
    Packet.h \
    Packet_v1.h \
    PacketQueue.h \
    Bind_recv.h
DEPENDPATH += ../../client
INCLUDEPATH += ../../client/include
SOURCES += main_net.cpp \
    Client.cpp \
    ClientManager.cpp \
    Component_Session.cpp \
    Component_Channel.cpp
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
    -lmysqlpp \
    -L../../libs
FORMS += mainwindow.ui \
    accountconnection.ui \
    configuration_dialog.ui \
    roomdialog.ui \
    newchan.ui
QMAKE_CXXFLAGS += -D_GUI
debug {
QMAKE_CXXFLAGS += -D_DEBUG -g3 -pg
}
else {
QMAKE_CXXFLAGS += -D_NDEBUG
}