CONFIG += debug_and_releae

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

unix:QT += x11extras
unix:LIBS += -lX11 -lxcb

# Input
HEADERS += \
    src/dirs.h \
    src/skin.h \
    src/plugin.h \
    src/shortcut_class.h \
    src/global_shortcut_class.h \
    src/command.h \
    src/system.h \
    src/parser.h \
    src/launcher.h \
\
    src/api.h \
    src/api/api_common.h \
    src/api/api_sys.h \
    src/api/api_console.h \
    #src/api/api_module.h \
    src/api/api_skin.h \
    src/api/api_plugin.h \
    src/api/api_shortcut.h \
    src/api/api_parser.h \
    src/api/api_launcher.h \
    #src/api/api_file.h \
    #src/api/api_clipboard.h \
    #src/api/api_http.h \
    #src/api/api_socket.h \
    src/api/api_widgets.h \
\
    src/widget/widget.h \
    src/widget/widget_proto.h \
    src/widget/window.h \
    src/widget/label.h \
    src/widget/label_proto.h \
    src/widget/line_edit.h \
    src/widget/line_edit_proto.h \
    src/widget/string_list_view.h \
    src/widget/string_list_view_proto.h \
    src/widget/abstract_button.h \
    src/widget/abstract_button_proto.h \
    src/widget/push_button.h \
    src/widget/radio_button.h \
    src/widget/checkbox.h

SOURCES += \
    src/main.cc \
    src/dirs.cc \
    src/skin.cc \
    src/plugin.cc \
    src/shortcut_class.cc \
    src/global_shortcut_class.cc \
    src/system.cc \
    src/parser.cc \
    src/launcher.cc \
\
    src/api/api_common.cc \
    src/api/api_sys.cc \
    src/api/api_console.cc \
    #src/api/api_module.cc \
    src/api/api_skin.cc \
    src/api/api_plugin.cc \
    src/api/api_shortcut.cc \
    src/api/api_parser.cc \
    src/api/api_launcher.cc \
    #src/api/api_file.cc \
    #src/api/api_clipboard.cc \
    #src/api/api_http.cc \
    #src/api/api_socket.cc \
    src/api/api_widgets.cc \
\
    src/widget/widget.cc \
    src/widget/widget_proto.cc \
    src/widget/window.cc \
    src/widget/label.cc \
    src/widget/label_proto.cc \
    src/widget/line_edit.cc \
    src/widget/line_edit_proto.cc \
    src/widget/string_list_view.cc \
    src/widget/string_list_view_proto.cc \
    src/widget/abstract_button.cc \
    src/widget/abstract_button_proto.cc \
    src/widget/push_button.cc \
    src/widget/radio_button.cc \
    src/widget/checkbox.cc

HEADERS += \
    src/qglobalshortcut.h
SOURCES += \
    src/qglobalshortcut.cc

win32:SOURCES += \
    src/qglobalshortcut_win.cc
unix:SOURCES += \
    src/qglobalshortcut_x11.cc

OTHER_FILES += \
    assets/.cllaun

# Assets auto copy
mkpath($$DESTDIR/plugins)
mkpath($$DESTDIR/plugins/script)
mkpath($$DESTDIR/skins)
# skin-api test
mkpath($$DESTDIR/skins/test_skin)
# plugin-api test
mkpath($$DESTDIR/plugins/script/foo/bar/baz)

win32 {
    QMAKE_POST_LINK += "copy /y $$system_path(assets/skins/test_skin/style.qss) $$system_path($$DESTDIR/skins/test_skin/) &"
    QMAKE_POST_LINK += "copy /y $$system_path(assets/skins/test_skin/launcher_back.png) $$system_path($$DESTDIR/skins/test_skin/) &"
    QMAKE_POST_LINK += "copy /y $$system_path(assets/.cllaun) $$system_path($$DESTDIR/) &"
# plugin-api test
    QMAKE_POST_LINK += "copy /y $$system_path(assets/plugins/script/foo/__init__.js) $$system_path($$DESTDIR/plugins/script/foo/) &"
    QMAKE_POST_LINK += "copy /y $$system_path(assets/plugins/script/foo/bar/__init__.js) $$system_path($$DESTDIR/plugins/script/foo/bar/) &"
    QMAKE_POST_LINK += "copy /y $$system_path(assets/plugins/script/foo/bar/baz/__init__.js) $$system_path($$DESTDIR/plugins/script/foo/bar/baz/) &"
}
else {
    QMAKE_POST_LINK += "cp -f $$system_path(assets/skins/test_skin/style.qss) $$system_path($$DESTDIR/skins/test_skin/) &"
    QMAKE_POST_LINK += "cp -f $$system_path(assets/skins/test_skin/launcher_back.png) $$system_path($$DESTDIR/skins/test_skin/) &"
    QMAKE_POST_LINK += "cp -f $$system_path(assets/.cllaun) $$system_path($$DESTDIR/) &"
# plugin-api test
    QMAKE_POST_LINK += "cp -f $$system_path(assets/plugins/script/foo/__init__.js) $$system_path($$DESTDIR/plugins/script/foo/) &"
    QMAKE_POST_LINK += "cp -f $$system_path(assets/plugins/script/foo/bar/__init__.js) $$system_path($$DESTDIR/plugins/script/foo/bar/) &"
    QMAKE_POST_LINK += "cp -f $$system_path(assets/plugins/script/foo/bar/baz/__init__.js) $$system_path($$DESTDIR/plugins/script/foo/bar/baz/) &"
}
