#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T11:17:48
#
#-------------------------------------------------

ARCH      = x86

inst1.files += fcitx_ubuntukylin.png
inst1.path = /usr/share/pixmaps
inst2.files += fcitx-qimpanel-configtool.desktop
inst2.path = /usr/share/applications
inst3.files += po/fcitx_skin_zh_CN.qm
inst3.path = /usr/share/fcitx-qimpanel

target.source += $$TARGET
target.path = /usr/bin
INSTALLS += inst1 \
    inst2 \
    inst3 \
    target

QT += core gui declarative dbus

TARGET = fcitx-qimpanel-configtool

LIBS += -lfcitx-qt -lfcitx-config -lfcitx-utils -lQtDBus

CONFIG +=

SOURCES += main.cpp \
    mainwindow.cpp \
    main_model.cpp \
    skin/skinbase.cpp \
    skin/skinfcitx.cpp \
    candidate_word.cpp \
    editingskindialog.cpp


HEADERS += mainwindow.h \
    main_model.h \
    skin/skinbase.h \
    kimpanelagenttype.h \
    candidate_word.h \
    editingskindialog.h \
    skin/skinfcitx.h



FORMS += mainwindow.ui \
    editingskindialog.ui

RESOURCES += \
    main.qrc

OTHER_FILES +=
