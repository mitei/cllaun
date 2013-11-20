CONFIG += debug_and_release

CONFIG(debug, debug|release) {
    suffix = _debug
    base_dir = debug
}
CONFIG(release, debug|release) {
    suffix = ""
    base_dir = release
}

OBJECTS_DIR = obj/$${base_dir}
MOC_DIR = moc/$${base_dir}
RCC_DIR = rcc/$${base_dir}
UI_DIR = ui/$${base_dir}


TEMPLATE = app
TARGET = cllaun$${suffix}
DESTDIR = build/bin

QT += core gui widgets qml script

INCLUDEPATH += src

# Input
HEADERS += src/main_window.h \
    src/launcher.h \
    src/plugin.h \
    src/api_common.h \
    src/api.h

SOURCES += src/main.cc \
    src/main_window.cc \
    src/launcher.cc \
    src/plugin.cc \
    src/api_common.cc

OTHER_FILES += assets_copy.bat assets_copy.sh

# Assets auto copy
mkpath($$DESTDIR/plugins)
mkpath($$DESTDIR/plugins/cllaun)
mkpath($$DESTDIR/skins)
mkpath($$DESTDIR/skins/test_skin)

# TODO
win32 {
    system(.\\assets_copy.bat)
}
else {
    system(./assets_copy.sh)
}
