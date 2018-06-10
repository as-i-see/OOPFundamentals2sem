QT += core testlib sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_tests.cpp

LIBS += -L"C:\Program Files (x86)\PostgreSQL\10\lib"
INCLUDEPATH += "C:\Program Files (x86)\PostgreSQL\10\include"
