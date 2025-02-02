QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GTestSetupFunctions.cpp \
    codefield.cpp \
    createnewprojectwindow.cpp \
    main.cpp \
    startMenu.cpp \
    windowmanager.cpp

HEADERS += \
    GTestSetupFunctions.hpp \
    StyleSheets.h \
    codefield.h \
    createnewprojectwindow.h \
    startMenu.h \
    windowmanager.h

FORMS += \
    createnewprojectwindow.ui \
    startMenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
