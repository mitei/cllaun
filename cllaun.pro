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


skin_files += \
    assets/skins/test_skin/style.qss \
    assets/skins/test_skin/launcher_back.png \

plugin_files += \
    assets/plugins/cllaun/common.js

OTHER_FILES += \
    $$skin_files \
    $$plugin_files



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
