TEMPLATE = lib
CONFIG += static
TARGET = cllaun
DESTDIR = ../build/lib
INCLUDEPATH += src
# QT += core gui widgets

# Input
HEADERS += src/common.h src/launcher.h
SOURCES += src/common.cc src/launcher.cc
