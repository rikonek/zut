include(../gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

SOURCES += \
    main.cpp \
    $$PWD/../../../src/Picture.cpp \
    $$PWD/../../../src/Rectangle.cpp \
    $$PWD/../../../src/Triangle.cpp

HEADERS += \
    tst_labtest.h \
    $$PWD/../../../src/IShape.hpp \
    $$PWD/../../../src/Picture.hpp \
    $$PWD/../../../src/Rectangle.hpp \
    $$PWD/../../../src/Triangle.hpp
