CONFIG += static debug_and_release

CONFIG(debug, debug|release) {
    suffix = _debug
    base_dir = cllaun_core/debug
}
CONFIG(release, debug|release) {
    suffix = ""
    base_dir = cllaun_core/release
}

OBJECTS_DIR = ../obj/$${base_dir}
MOC_DIR = ../moc/$${base_dir}
RCC_DIR = ../rcc/$${base_dir}
UI_DIR = ../ui/$${base_dir}

TEMPLATE = lib
TARGET = cllaun$${suffix}
DESTDIR = ../build/lib

INCLUDEPATH += src
# QT += core gui widgets

# Input
HEADERS += src/common.h src/launcher.h
SOURCES += src/common.cc src/launcher.cc

win:SOURCES += src/launcher_win.cc
