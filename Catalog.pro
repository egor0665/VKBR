QT       += core gui sql charts printsupport testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += libpq.dll

QTPLUGIN += QPSQL

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#DEFINES += QT_NO_DEBUG_OUTPUT
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += \
    DBbooster_rocket.cpp \
    DBlaunch.cpp \
    DBorganization.cpp \
    DBspaceport.cpp \
    DBunit.cpp \
    DBupper_block.cpp \
    database.cpp \
    dbproject.cpp \
    dbspacecraft.cpp \
    dbuser.cpp \
    filemanager.cpp \
    fileprojectvalue.cpp \
    main.cpp \
    mainmodel.cpp \
    mainwindow.cpp \
    predictionmodel.cpp \
    projectset.cpp \
    savetopdfdialog.cpp \
    tabcatalogandcomparisonmodel.cpp \
    tabeditusermodel.cpp \
    tabnewcraftmodel.cpp \
    tabnewextrasmodel.cpp \
    tabnewprojectmodel.cpp \
    tabpredictionmodel.cpp \
    test_tests.cpp \
    unitcomparator.cpp \
    userloginwindow.cpp

HEADERS += \
    DBbooster_rocket.h \
    DBlaunch.h \
    DBorganization.h \
    DBspacecraft.h \
    DBspaceport.h \
    DBunit.h \
    DBupper_block.h \
    PALETTE.h \
    comparevalue.h \
    database.h \
    dbproject.h \
    dbuser.h \
    filemanager.h \
    fileprojectvalue.h \
    mainmodel.h \
    mainwindow.h \
    predictionmodel.h \
    projectset.h \
    savetopdfdialog.h \
    tabcatalogandcomparisonmodel.h \
    tabeditusermodel.h \
    tabnewcraftmodel.h \
    tabnewextrasmodel.h \
    tabnewprojectmodel.h \
    tabpredictionmodel.h \
    test_tests.h \
    unitcomparator.h \
    userloginwindow.h

FORMS += \
    mainwindow.ui \
    savetopdfdialog.ui \
    userloginwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
