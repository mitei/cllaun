# # TODO
# * モジュールプラグイン
#   * class Module
#
#
TARGET = cllaun
TEMPLATE = app
CONFIG += debug_and_release
QT += core gui widgets

DESTDIR = dest/cllaun
DEFINES += BUILDING_CLLAUN

INCLUDEPATH += src

V8_BASEDIR = third_party/v8

CONFIG(debug, debug|release) {
    V8_LIBDIR = $${V8_BASEDIR}/build/Debug/lib
}
CONFIG(release, debug|release) {
    V8_LIBDIR = $${V8_BASEDIR}/build/Release/lib
}

# V8 INCLUDEPATH, LIBS
INCLUDEPATH += $${V8_BASEDIR}/include
win32:LIBS += \
    $$absolute_path($${V8_LIBDIR}/v8_base.ia32.lib) \
    $$absolute_path($${V8_LIBDIR}/v8_snapshot.lib) \
    $$absolute_path($${V8_LIBDIR}/icui18n.lib) \
    $$absolute_path($${V8_LIBDIR}/icuuc.lib) \
    'C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib/ws2_32.lib' \
    'C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib/winmm.lib' \
    'C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib/advapi32.lib'


# SOURCES, HEADERS
HEADERS += \
    src/cllaun.h \
    src/cllaun_internal.h \
    src/dirs.h \
    src/module.h \
    src/module/system.h \
    src/module/console.h \
    src/module/modules.h \
    src/module/widgets.h
SOURCES += \
    src/main.cc \
    src/cllaun.cc \
    src/cllaun_internal.cc \
    src/dirs.cc \
    #src/module.cc \
    src/module/system.cc \
    src/module/console.cc \
    src/module/modules.cc \
    src/module/widgets.cc

