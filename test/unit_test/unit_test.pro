#-------------------------------------------------
#
# Project created by QtCreator 2013-11-26T00:54:33
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_unit_parsertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    ../../src/parser.cc \
    ../../src/parser_util.cc \
    tst_unit_parsertest.cc
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/command.h \
    ../../src/parser.h \
    ../../src/parser_util.h \
    ../../src/lib/container_make.h \
