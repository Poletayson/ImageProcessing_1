#-------------------------------------------------
#
# Project created by QtCreator 2018-09-11T16:00:52
#
#-------------------------------------------------

QT       += core gui widgets


QMAKE_LIBS+=-static

QMAKE_CXXFLAGS+=-msse3



#QMAKE_CXXFLAGS+=-U_WIN32

TARGET = ImageProcessing
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    descriptor.cpp \
    descriptorconstructor.cpp \
    doubleimagemono.cpp \
    doubleimagergb.cpp \
    idoubleimage.cpp \
    interestingpoint.cpp \
        main.cpp \
        mainwindow.cpp \
    graphic.cpp \
    octave.cpp \
    pyramideimage.cpp \
    utils.cpp

HEADERS += \
    descriptor.h \
    descriptorconstructor.h \
    doubleimagemono.h \
    doubleimagergb.h \
    idoubleimage.h \
    interestingpoint.h \
        mainwindow.h \
    graphic.h \
    octave.h \
    pyramideimage.h \
    utils.h


FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
