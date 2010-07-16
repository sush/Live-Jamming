# -------------------------------------------------
# Project created by QtCreator 2010-03-18T13:38:22
# -------------------------------------------------
include(../livejamming.pri)
RESOURCES = app.qrc
TARGET = livejamming_client
DESTDIR = ..
TEMPLATE = app
!contains(DEFINES, NO_MULTIMEDIA) {
QT += multimedia
SOURCES += nespaudio.cpp
HEADERS += nespaudio.h
#FOR SPECTRE
INCLUDEPATH += spectre
DEPENDPATH += spectre
SOURCES += engine.cpp \
    frequencyspectrum.cpp \
    levelmeter.cpp \
    mainwidget.cpp \
    progressbar.cpp \
    settingsdialog.cpp \
    spectrograph.cpp \
    spectrumanalyser.cpp \
    tonegenerator.cpp \
    tonegeneratordialog.cpp \
    utils.cpp \
    waveform.cpp \
    wavfile.cpp
HEADERS += engine.h \
    frequencyspectrum.h \
    levelmeter.h \
    mainwidget.h \
    progressbar.h \
    settingsdialog.h \
    spectrograph.h \
    spectrum.h \
    spectrumanalyser.h \
    tonegenerator.h \
    tonegeneratordialog.h \
    utils.h \
    waveform.h \
    wavfile.h
fftreal_dir = ../3rdparty/fftreal
INCLUDEPATH += $${fftreal_dir}

!contains(DEFINES, DISABLE_FFT) {
        macx {
            # Link to fftreal framework
            LIBS += -F$${fftreal_dir}
            LIBS += -framework fftreal
        } else {
            LIBS += -L..
            LIBS += -lfftreal
        }
}
#OTHER
}
#FOR GUI
SOURCES += mainwindow.cpp \
    accountconnection.cpp \
    configuration_dialog.cpp \
    roomdialog.cpp \
    proxy.cpp \
    channellist.cpp \
    conversationset.cpp \
    roomplayeritem.cpp
HEADERS += mainwindow.h \
    accountconnection.h \
    configuration_dialog.h \
    roomdialog.h \
    proxy.h \
    channellist.h \
    conversationset.h \
    roomplayeritem.h

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
    Channel.cpp \
    Room.cpp \
    Jam.cpp
HEADERS += Session.h \
    Manager.h \
    Packet.h \
    Packet_v1.h \
    PacketQueue.h \
    Bind_recv.h \
    Packet_v1_Session.h \
    Packet_v1_Channel.h \
    Packet_v1_Friend.h
DEPENDPATH += ../../../../client
INCLUDEPATH += ../../../../client/include
SOURCES += main_net.cpp \
    Client.cpp \
    ClientManager.cpp \
    Component_Session.cpp \
    Component_Friend.cpp \
    Component_Channel.cpp \
    Component_Room.cpp \
    Component_Jam.cpp
HEADERS += Audio.h \
    Client.h \
    ClientManager.h \
    Component_Session.h \
    Component_Friend.h \
    Component_Channel.h \
    Component_Room.h
INCLUDEPATH += ../../../../include/boost
HEADERS += threadpool.hpp
INCLUDEPATH += ../../../../server/include
HEADERS += Config.h
INCLUDEPATH += ../../../../include
HEADERS += Protocol.h
LIBS += -lboost_system \
    -lboost_thread-mt \
    -lboost_program_options \
    -lyaml-cpp \
    -L../../../../libs \
    -L/usr/share/qt4/lib
FORMS += mainwindow.ui \
    accountconnection.ui \
    configuration_dialog.ui \
    roomdialog.ui \
    newchan.ui \
    chanlist.ui \
    conversationset.ui \
    roomplayeritem.ui
DEFINES += _GUI
debug:QMAKE_CXXFLAGS += -D_DEBUG \
    -g3 \
    -pg
else:QMAKE_CXXFLAGS += -D_NDEBUG
unix: {
# Provide relative path from application to fftreal library
QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN
}
