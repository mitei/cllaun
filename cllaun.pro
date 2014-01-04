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
DESTDIR = dest/cllaun

QT += core gui widgets script

unix:QMAKE_CXXFLAGS += "-std=c++11"

INCLUDEPATH += src

# Input
HEADERS += \
    src/dirs.h \
    src/skin.h \
    src/config.h \
    #src/commands.h \
    #src/main_window.h \
    src/launcher.h \
    src/api.h \
    src/api_common.h \
    src/api_console.h \
    #src/api_module.h \
    src/api_config.h \
    src/api_skin.h \
    #src/api_commands.h \
    #src/api_alias.h \
    #src/api_file.h \
    #src/api_clipboard.h \
    #src/api_http.h \
    #src/api_socket.h \
    src/api_widgets.h

SOURCES += \
    src/main.cc \
    src/dirs.cc \
    src/skin.cc \
    src/config.cc \
    #src/commands.cc \
    #src/main_window.cc \
    src/launcher.cc \
    src/api_common.cc \
    src/api_console.cc \
    #src/api_module.cc \
    src/api_config.cc \
    src/api_skin.cc \
    #src/api_commands.cc \
    #src/api_alias.cc \
    #src/api_file.cc \
    #src/api_clipboard.cc \
    #src/api_http.cc \
    #src/api_socket.cc \
    src/api_widgets.cc

win:SOURCES += src/launcher_win.cc

OTHER_FILES += \
    assets/.cllaun

# Assets auto copy
mkpath($$DESTDIR/plugins)
mkpath($$DESTDIR/plugins/cllaun)
mkpath($$DESTDIR/skins)
mkpath($$DESTDIR/skins/test_skin)

win32 {
    QMAKE_POST_LINK += "copy /y $$system_path(assets/skins/test_skin/style.qss) $$system_path($$DESTDIR/skins/test_skin/) &"
    QMAKE_POST_LINK += "copy /y $$system_path(assets/skins/test_skin/launcher_back.png) $$system_path($$DESTDIR/skins/test_skin/) &"
    QMAKE_POST_LINK += "copy /y $$system_path(assets/.cllaun) $$system_path($$DESTDIR/) &"
}
else {
    QMAKE_POST_LINK += "cp -f $$system_path(assets/skins/test_skin/style.qss) $$system_path($$DESTDIR/skins/test_skin/) &"
    QMAKE_POST_LINK += "cp -f $$system_path(assets/skins/test_skin/launcher_back.png) $$system_path($$DESTDIR/skins/test_skin/) &"
    QMAKE_POST_LINK += "cp -f $$system_path(assets/.cllaun) $$system_path($$DESTDIR/) &"
}
