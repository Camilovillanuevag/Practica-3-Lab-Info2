TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        archivos.cpp \
        encriptacion.cpp \
        lz78.cpp \
        main.cpp \
        rle.cpp

HEADERS += \
    archivos.h \
    encriptacion.h \
    lz78.h \
    rle.h
