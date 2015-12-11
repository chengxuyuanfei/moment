TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    example-suite.c \
    unit_test.c \
    c_time_format_conversion.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    greatest.h \
    unit_test.h \
    c_timespan.h \
    c_time_format_conversion.h

DISTFILES += \
    moment.pro.user

