QT       += core gui sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


#INCLUDEPATH += "C:/Program Files (x86)/PostgreSQL/9.6/lib"
#INCLUDEPATH += "C:/Program Files (x86)/PostgreSQL/9.6/lib/libpq.dll"
#INCLUDEPATH += "C:/Program Files (x86)/PostgreSQL/9.6/"

INCLUDEPATH += libpq.dll
#INCLUDEPATH += libpq.lib
#INCLUDEPATH += qsqlpsql.dll
#INCLUDEPATH += qsqlpsqld.dll

#LIBS += libpq.dll
#LIBS += libpq.lib
#LIBS += qsqlpsql.dll
#LIBS += qsqlpsqld.dll

#INCLUDEPATH += "C:/Program Files (x86)/PostgreSQL/9.6/include"
#INCLUDEPATH += "sqldrivers"
#INCLUDEPATH += "lib"

#LIBS += "C:/Program Files (x86)/PostgreSQL/9.6/lib/libpq.dll"

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
    chartview.cpp \
    database.cpp \
    dbproject.cpp \
    dbspacecraft.cpp \
    main.cpp \
    mainmodel.cpp \
    mainwindow.cpp \
    menu.cpp \
    predictionmodel.cpp \
    projectset.cpp \
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
    chartdialog.h \
    chartview.h \
    comparevalue.h \
    database.h \
    dbChangeValue.h \
    dbproject.h \
    mainmodel.h \
    mainwindow.h \
    menu.h \
    predictionmodel.h \
    projectset.h \
    unitcomparator.h \
    userloginwindow.h

FORMS += \
    chartdialog.ui \
    mainwindow.ui \
    userloginwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
