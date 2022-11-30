#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql
QT       += core gui sql charts
QT += serialport
QT += printsupport
#LIBS += -lqrencode
QT+= sql axcontainer widgets qml  quickwidgets quick opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    arduino.cpp \
    dialog.cpp \
    employe.cpp \
    event.cpp \
    login.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    qrcode.cpp \
    reservation.cpp \
    secformdialog.cpp \
    smtp.cpp \
    sqleventmodel.cpp

HEADERS += \
    arduino.h \
    dialog.h \
    employe.h \
    event.h \
    login.h \
        mainwindow.h \
    connection.h \
    qrcode.h \
    qtquickcontrolsapplication.h \
    reservation.h \
    secformdialog.h \
    smtp.h \
    sqleventmodel.h

FORMS += \
        dialog.ui \
        mainwindow.ui \
        secformdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/bin.png \
    images/edit.png \
    images/eventindicator.png \
    images/logo_c++-1.png \
    images/options.png \
    images/search.png \
    qml/main.qml

RESOURCES += \
    Resources.qrc






