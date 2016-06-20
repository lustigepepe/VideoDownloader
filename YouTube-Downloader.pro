#-------------------------------------------------
#
# Project created by QtCreator 2016-06-09T21:36:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YouTube-Downloader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

macx {
    ## For C++11 VERSION
    #QMAKE_CXXFLAGS += -std=c++11
    ## Openssl
    _OPENSSL_PATH = /usr/local/Cellar/openssl/1.0.2g
    INCLUDEPATH += "$${_OPENSSL_PATH}/include/"
    LIBS += -L$${_OPENSSL_PATH}/lib -lssl -lcrypto

    ## Boost
    _BOOST_PATH = /usr/local/Cellar/boost/1.60.0_1
    INCLUDEPATH += "$${_BOOST_PATH}/include/"
    LIBS += -L$${_BOOST_PATH}/lib
    ## Use only one of these:
    LIBS += -lboost_chrono-mt -lboost_system # using dynamic lib (not sure if you need that "-mt" at the end or not)
    #LIBS += $${_BOOST_PATH}/lib/libboost_chrono-mt.a # using static lib
}
