QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Models/recent_project_data.cpp \
    create_proj.cpp \
    Models/historyitem.cpp \
    main.cpp \
    application.cpp \
    mwmenubar.cpp \
    Models/projectdata.cpp \
    recent_project.cpp

HEADERS += \
    Models/recent_project_data.h \
    application.h \
    create_proj.h \
    Models/historyitem.h \
    mwmenubar.h \
    Models/projectdata.h \
    recent_project.h

FORMS += \
    application.ui \
    create_proj.ui \
    recent_project.ui

TRANSLATIONS += \
    triplet_labeling_en_GB.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
