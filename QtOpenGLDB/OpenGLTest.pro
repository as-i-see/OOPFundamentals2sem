#-------------------------------------------------
#
# Project created by QtCreator 2018-03-25T02:04:23
#
#-------------------------------------------------

QT       += core gui widgets opengl sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGLTest
TEMPLATE = app
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
LIBS += opengl32.lib
LIBS += -L"C:\Program Files (x86)\PostgreSQL\10\lib"
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    scene.cpp \
    newactionform.cpp \
    transform3d.cpp \
    cubecreation.cpp \
    saver.cpp \
    input.cpp \
    camera3d.cpp \
    toolbar.cpp \
    cube.cpp

HEADERS += \
        mainwindow.h \
    newactionform.h \
    scene.h \
    vertex.h \
    transform3d.h \
    cubecreation.h \
    saver.h \
    input.h \
    camera3d.h \
    toolbar.h \
    cube.h

FORMS += \
    mainwindow.ui \
    newactionform.ui \
    cubecreation.ui \
    saver.ui

DISTFILES += \
    shaders/simple.frag \
    shaders/simple.vert

RESOURCES += \
    resources.qrc

INCLUDEPATH += "C:\Program Files (x86)\PostgreSQL\10\include"
