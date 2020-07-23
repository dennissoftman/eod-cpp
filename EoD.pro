TARGET=EoD.x86_64
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lSDL2 -lSDL2_image -ltar -lz -lm -lyaml-cpp

SOURCES += \
        main.cpp \
        src/*.cpp

HEADERS += include/*.hpp
