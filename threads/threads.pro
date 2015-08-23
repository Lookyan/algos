TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /home/alex/Загрузки/boost_1_57_0/

LIBS += \
       -lboost_system\
       -lboost_thread\

SOURCES += main.cpp

