#-------------------------------------------------
#
# Project created by QtCreator 2018-03-25T02:04:23
#
#-------------------------------------------------

QT       += core gui widgets opengl sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTGLDB
TEMPLATE = app
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
LIBS += opengl32.lib glu32.lib
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
    input.cpp \
    camera3d.cpp \
    toolbar.cpp \
    saver.cpp \
    loader.cpp \
    prism.cpp \
    prismcreation.cpp \
    preferenceseditor.cpp \
    figure.cpp \
    dbaccessor.cpp \
    camera3d.cpp \
    dbaccessor.cpp \
    figure.cpp \
    input.cpp \
    loader.cpp \
    main.cpp \
    mainwindow.cpp \
    newactionform.cpp \
    preferenceseditor.cpp \
    prism.cpp \
    prismcreation.cpp \
    saver.cpp \
    scene.cpp \
    toolbar.cpp \
    transform3d.cpp \
    camera3d.cpp \
    dbaccessor.cpp \
    figure.cpp \
    input.cpp \
    loader.cpp \
    main.cpp \
    mainwindow.cpp \
    newactionform.cpp \
    preferenceseditor.cpp \
    prism.cpp \
    prismcreation.cpp \
    saver.cpp \
    scene.cpp \
    toolbar.cpp \
    transform3d.cpp \
    cylinder.cpp \
    cylindercreation.cpp

HEADERS += \
        mainwindow.h \
    newactionform.h \
    scene.h \
    vertex.h \
    transform3d.h \
    input.h \
    camera3d.h \
    toolbar.h \
    saver.h \
    loader.h \
    prism.h \
    prismcreation.h \
    preferenceseditor.h \
    figure.h \
    dbaccessor.h \
    camera3d.h \
    dbaccessor.h \
    figure.h \
    input.h \
    loader.h \
    mainwindow.h \
    newactionform.h \
    preferenceseditor.h \
    prism.h \
    prismcreation.h \
    saver.h \
    scene.h \
    toolbar.h \
    transform3d.h \
    vertex.h \
    camera3d.h \
    dbaccessor.h \
    figure.h \
    input.h \
    loader.h \
    mainwindow.h \
    newactionform.h \
    preferenceseditor.h \
    prism.h \
    prismcreation.h \
    saver.h \
    scene.h \
    toolbar.h \
    transform3d.h \
    vertex.h \
    cylinder.h \
    cylindercreation.h

FORMS += \
    mainwindow.ui \
    newactionform.ui \
    saver.ui \
    loader.ui \
    prismcreation.ui \
    preferenceseditor.ui \
    cylindercreation.ui

RESOURCES += \
    resources.qrc

INCLUDEPATH += "C:\Program Files (x86)\PostgreSQL\10\include"
