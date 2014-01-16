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
win32:LIBS += shell32.lib

# Input
HEADERS += \
    src/dirs.h \
    src/skin.h \
    src/config.h \
    src/shortcut_class.h \
    src/command.h \
    src/api/api_shortcut.h \
    src/parser.h \
    #src/main_window.h \
    src/launcher.h \
    src/api.h \
    src/api/api_common.h \
    src/api/api_console.h \
    #src/api/api_module.h \
    src/api/api_config.h \
    src/api/api_skin.h \
    src/api/api_parser.h \
    src/api/api_launcher.h \
    #src/api/api_file.h \
    #src/api/api_clipboard.h \
    #src/api/api_http.h \
    #src/api/api_socket.h \
    src/api/api_widgets.h \
    src/widget/widget.h \
    src/widget/line_edit.h

SOURCES += \
    src/main.cc \
    src/dirs.cc \
    src/skin.cc \
    src/config.cc \
    src/shortcut_class.cc \
    src/parser.cc \
    #src/main_window.cc \
    src/launcher.cc \
    src/api/api_common.cc \
    src/api/api_console.cc \
    #src/api/api_module.cc \
    src/api/api_config.cc \
    src/api/api_skin.cc \
    src/api/api_shortcut.cc \
    src/api/api_parser.cc \
    src/api/api_launcher.cc \
    #src/api/api_file.cc \
    #src/api/api_clipboard.cc \
    #src/api/api_http.cc \
    #src/api/api_socket.cc \
    src/api/api_widgets.cc \
    src/widget/widget.cc \
    src/widget/line_edit.cc

#win:SOURCES += src/launcher_win.cc

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
