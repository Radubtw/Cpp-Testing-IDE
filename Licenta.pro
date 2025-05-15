QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clickablelabel.cpp \
    codefield.cpp \
    createnewprojectwindow.cpp \
    generatedtextedit.cpp \
    generatetestdialog.cpp \
    inputtextedit.cpp \
    main.cpp \
    menubar.cpp \
    newcmakeprojectfunctions.cpp \
    opennewprojectdialog.cpp \
    outputsection.cpp \
    parser.cpp \
    processes.cpp \
    startMenu.cpp \
    terminal.cpp \
    testresultswindow.cpp \
    testwrapper.cpp \
    windowmanager.cpp

HEADERS += \
    ExpectCall.h \
    StyleSheets.h \
    clickablelabel.h \
    codefield.h \
    createnewprojectwindow.h \
    generatedtextedit.h \
    generatetestdialog.h \
    inputtextedit.h \
    menubar.h \
    newcmakeprojectconstants.h \
    newcmakeprojectfunctions.h \
    opennewprojectdialog.h \
    outputsection.h \
    parser.h \
    parserConstants.h \
    processes.hpp \
    startMenu.h \
    terminal.h \
    testresultswindow.h \
    testwrapper.h \
    windowmanager.h

FORMS += \
    createnewprojectwindow.ui \
    startMenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc \
