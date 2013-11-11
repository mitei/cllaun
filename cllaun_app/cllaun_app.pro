
CONFIG += debug_and_release

CONFIG(debug, debug|release) {
    suffix = _debug
    base_dir = cllaun_app/debug
}
CONFIG(release, debug|release) {
    suffix = ""
    base_dir = cllaun_app/release
}

OBJECTS_DIR = ../obj/$${base_dir}
MOC_DIR = ../moc/$${base_dir}
RCC_DIR = ../rcc/$${base_dir}
UI_DIR = ../ui/$${base_dir}

TEMPLATE = app
TARGET = cllaun$${suffix}
DESTDIR = ../build/bin

QT += core gui widgets qml script

DEPENDPATH += ../cllaun_core

INCLUDEPATH += src ../cllaun_core/src
win32 {
    LIBS += ../build/lib/cllaun$${suffix}.lib
}
else {
    LIBS += ../build/lib/libcllaun$${suffix}.a
}

# Input
HEADERS += src/main_window.h
SOURCES += src/main.cc src/main_window.cc

OTHER_FILES += \
    assets/style.qss \
    assets/launcher_back.png

# Assets auto copy
win32 {
    !exists($$DESTDIR/assets) {
        QMAKE_POST_LINK += "mkdir $$system_path($$DESTDIR/assets) &"
    }
    for(FILE, OTHER_FILES) {
        QMAKE_POST_LINK += "copy /y $$system_path($$FILE) $$system_path($$DESTDIR/assets/) &"
    }
}
else {
    !exists($$DESTDIR/assets) {
        QMAKE_POST_LINK += "mkdir $$system_path($$DESTDIR/assets) &"
    }
    QMAKE_POST_LINK += "cp -f $$OTHER_FILES $$DESTDIR/assets &"
}
