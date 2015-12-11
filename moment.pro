TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    example-suite.c \
    unit_test.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    greatest.h \
    unit_test.h \
    c_timespan.h

DISTFILES += \
    moment.pro.user

