#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T16:18:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
TARGET = SemesterprojektPI
TEMPLATE = app

# So wiringPi include files can be found during compile
INCLUDEPATH    += /usr/local/include

# To link the wiringPi library when making the executable
LIBS += -L/usr/local/lib -lwiringPi

SOURCES += main.cpp\
		Send120kHz.cpp\
		 
HEADERS  += Send120kHz.h\