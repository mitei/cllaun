TEMPLATE = subdirs
CONFIG += orderd debug_and_release

SUBDIRS = cllaun_core \
            cllaun_app

cllaun_app.depends = cllaun_core
