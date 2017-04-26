TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    smartarray.cpp \
    smartmatrix.cpp \
    smartdoublearray.cpp \
    fraction.cpp \
    mixednumber.cpp

HEADERS += \
    smartarray.h \
    smartmatrix.h \
    smartdoublearray.h \
    fraction.h \
    mixednumber.h
