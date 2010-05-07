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
FORMS += mainwindow.ui \
    accountconnection.ui \
    configuration_dialog.ui \
    roomdialog.ui
CONFIG += link_pkgconfig
PKGCONFIG += yaml-cpp
