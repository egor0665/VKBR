QT       += core gui sql charts printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += libpq.dll

QTPLUGIN += QPSQL

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DBbooster_rocket.cpp \
    DBlaunch.cpp \
    DBorganization.cpp \
    DBspaceport.cpp \
    DBunit.cpp \
    DBupper_block.cpp \
    chartdialog.cpp \
    chartmanager.cpp \
    chartview.cpp \
    database.cpp \
    dbproject.cpp \
    dbspacecraft.cpp \
    filemanager.cpp \
    fileprojectvalue.cpp \
    launchdata.cpp \
    main.cpp \
    mainmodel.cpp \
    mainwindow.cpp \
    menu.cpp \
    predictionmodel.cpp \
    projectset.cpp \
    savetopdfdialog.cpp \
    tabcatalogandcomparisonmodel.cpp \
    tabeditdbmodel.cpp \
    tabnewcraftmodel.cpp \
    tabnewextrasmodel.cpp \
    tabnewprojectmodel.cpp \
    tabpredictionmodel.cpp \
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
    chartdialog.h \
    chartmanager.h \
    chartview.h \
    comparevalue.h \
    database.h \
    dbChangeValue.h \
    dbproject.h \
    filemanager.h \
    fileprojectvalue.h \
    launchdata.h \
    mainmodel.h \
    mainwindow.h \
    menu.h \
    predictionmodel.h \
    projectset.h \
    savetopdfdialog.h \
    tabcatalogandcomparisonmodel.h \
    tabeditdbmodel.h \
    tabnewcraftmodel.h \
    tabnewextrasmodel.h \
    tabnewprojectmodel.h \
    tabpredictionmodel.h \
    unitcomparator.h \
    userloginwindow.h

FORMS += \
    chartdialog.ui \
    mainwindow.ui \
    savetopdfdialog.ui \
    userloginwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
