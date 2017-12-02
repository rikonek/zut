CONFIG -= qt
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

TARGET = lab2

SOURCES += main.cpp \
    Rectangle.cpp \
    Picture.cpp \
    Triangle.cpp

HEADERS += \
    IShape.hpp \
    Rectangle.hpp \
    Picture.hpp \
    Triangle.hpp
