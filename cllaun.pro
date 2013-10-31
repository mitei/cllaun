TEMPLATE = subdirs
CONFIG += orderd

SUBDIRS = cllaun_core \
            cllaun_app

cllaun_app.depends = cllaun_core
