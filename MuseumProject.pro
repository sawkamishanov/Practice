#-------------------------------------------------
#
# Project created by QtCreator 2018-06-29T16:36:56
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MuseumProject
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


SOURCES += \
    MainWindow/mainwindow.cpp \
    main.cpp \
    MuseumClass/museumsource.cpp \
    DataBase/database.cpp \
    DialogAddEvent/dialogaddevent.cpp \
    DialogAddMuseum/dialogaddmuseum.cpp \
    StartWindow/startwindow.cpp \
    HelpMenu/helpmenu.cpp

HEADERS += \
    MainWindow/mainwindow.h \
    EventClass/eventclass.h \
    MuseumClass/museumclass.h \
    DataBase/database.h \
    DialogAddEvent/dialogaddevent.h \
    DialogAddMuseum/dialogaddmuseum.h \
    StartWindow/startwindow.h \
    HelpMenu/helpmenu.h

FORMS += \
    MainWindow/mainwindow.ui \
    DialogAddEvent/dialogaddevent.ui \
    DialogAddMuseum/dialogaddmuseum.ui \
    StartWindow/startwindow.ui \
    HelpMenu/helpmenu.ui

RESOURCES += \
    resources.qrc

DISTFILES +=

