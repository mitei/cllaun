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

QT += core gui widgets script

unix:QMAKE_CXXFLAGS += "-std=c++11"

INCLUDEPATH += src

# Input
HEADERS += \
    src/core.h \
    src/dirs.h \
    src/skin.h \
    src/config.h \
    src/main_window.h \
    src/launcher.h \
    src/api.h \
    src/api_common.h \
    src/api_config.h \
    src/api_skin.h \
    src/api_file.h \
    src/api_clipboard.h \
    src/api_http.h \
    src/api_socket.h \
    src/api_skin.h \
    src/api_window.h

SOURCES += \
    src/main.cc \
    src/core.cc \
    src/dirs.cc \
    src/skin.cc \
    src/config.cc \
    src/api_config.cc \
    src/api_skin.cc \
    src/main_window.cc \
    src/launcher.cc \
    src/api_common.cc \
    src/api_file.cc \
    src/api_clipboard.cc \
    src/api_http.cc \
    src/api_socket.cc \
    src/api_skin.cc \
    src/api_window.cc

win:SOURCES += src/launcher_win.cc

OTHER_FILES += assets/default.cllaun_conf

# Assets auto copy
mkpath($$DESTDIR/plugins)
mkpath($$DESTDIR/plugins/cllaun)
mkpath($$DESTDIR/skins)
mkpath($$DESTDIR/skins/test_skin)

win32 {
    QMAKE_POST_LINK += "copy /y $$system_path(assets/skins/test_skin/style.qss) $$system_path($$DESTDIR/skins/test_skin/) &"
    QMAKE_POST_LINK += "copy /y $$system_path(assets/skins/test_skin/launcher_back.png) $$system_path($$DESTDIR/skins/test_skin/) &"
    QMAKE_POST_LINK += "copy /y $$system_path(assets/default.cllaun_conf) $$system_path($$DESTDIR/) &"
}
else {
    QMAKE_POST_LINK += "cp -f $$system_path(assets/skins/test_skin/style.qss) $$system_path($$DESTDIR/skins/test_skin/) &"
    QMAKE_POST_LINK += "cp -f $$system_path(assets/skins/test_skin/launcher_back.png) $$system_path($$DESTDIR/skins/test_skin/) &"
    QMAKE_POST_LINK += "cp -f $$system_path(assets/default.cllaun_conf) $$system_path($$DESTDIR/) &"
}
