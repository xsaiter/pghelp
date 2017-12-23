TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cc

INCLUDEPATH += /usr/include/postgresql
LIBS += /usr/lib/x86_64-linux-gnu/libpq.so

HEADERS += \
    pg_help.hh
