QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    Delivery.cpp \
    Factory.cpp \
    Generator.cpp \
    Item.cpp \
    Shop.cpp \
    Statistics.cpp \
    Warehouse.cpp

HEADERS += \
    Delivery.h \
    Factory.h \
    Generator.h \
    Interfaces.h \
    Item.h \
    Shop.h \
    Statistics.h \
    Warehouse.h \
    customdialog.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
