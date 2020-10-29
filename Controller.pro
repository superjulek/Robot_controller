QT       += core gui
QT       += bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bluetoothcommunicator.cpp \
    configurationwindow.cpp \
    joysticksteeringwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    joypad.cpp \
    manualsteeringwindow.cpp \
    telemetrywindow.cpp

HEADERS += \
    bluetoothcommunicator.h \
    configurationwindow.h \
    joysticksteeringwindow.h \
    mainwindow.h \
    joypad.h \
    manualsteeringwindow.h \
    telemetrywindow.h

FORMS += \
    configurationwindow.ui \
    joysticksteeringwindow.ui \
    mainwindow.ui \
    manualsteeringwindow.ui \
    telemetrywindow.ui

TRANSLATIONS += \
    Controller_en_GB.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
