QT       += core gui \
	network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    characterwidget.cpp \
    main.cpp \
    mudaetierlist.cpp \
    tierlistdata.cpp

HEADERS += \
    characterwidget.h \
    mudaetierlist.h \
    tierlistdata.h

FORMS += \
    characterwidget.ui \
    mudaetierlist.ui

TRANSLATIONS += \
    MudaeTierList_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
