QT       += core gui sql

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
    booster_rocket.cpp \
    database.cpp \
    databaseloginwindow.cpp \
    main.cpp \
    mainmodel.cpp \
    mainwindow.cpp \
    menu.cpp \
    organization.cpp \
    spaceport.cpp \
    unit.cpp \
    upper_block.cpp

HEADERS += \
    booster_rocket.h \
    database.h \
    databaseloginwindow.h \
    mainmodel.h \
    mainwindow.h \
    menu.h \
    organization.h \
    spaceport.h \
    unit.h \
    upper_block.h

FORMS += \
    databaseloginwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
