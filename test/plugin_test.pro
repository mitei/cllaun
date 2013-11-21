CONFIG += debug_and_release

TEMPLATE = app
TARGET = plugin_test
DESTDIR = dest

QT += core script

INCLUDEPATH += ../src src

HEADERS += ../src/plugin.h \
    ../src/api_common.h \
    src/debug.h \
    src/class_test.h

SOURCES += src/plugin_test.cc \
    ../src/plugin.cc \
    ../src/api_common.cc

OTHER_FILES += src/plugin_test.js
