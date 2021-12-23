QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    create_proj.cpp \
    historyitem.cpp \
    main.cpp \
    application.cpp \
    mwmenubar.cpp \
    projectdata.cpp

HEADERS += \
    application.h \
    create_proj.h \
    historyitem.h \
    mwmenubar.h \
    projectdata.h

FORMS += \
    application.ui \
    create_proj.ui

TRANSLATIONS += \
    triplet_labeling_en_GB.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
