#-------------------------------------------------
#
# Project created by QtCreator 2017-01-02T20:34:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Knn
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cvision.cpp

HEADERS  += mainwindow.h \
    cvision.h

FORMS    += mainwindow.ui

QT       += core gui


CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic -O3 -fopenmp

INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /usr/local/include/opencv2

LIBS += -L/usr/local/lib \
        -lopencv_shape \
        -lopencv_stitching \
        -lopencv_objdetect \
        -lopencv_superres \
        -lopencv_videostab \
        #-lippicv \
        -lopencv_calib3d \
        -lopencv_features2d \
        -lopencv_highgui \
        -lopencv_videoio \
        -lopencv_imgcodecs \
        -lopencv_video \
        -lopencv_photo \
        -lopencv_ml \
        -lopencv_imgproc \
        -lopencv_flann \
        -lopencv_core \
        -fopenmp

DISTFILES += \
    SegKnn.xml
