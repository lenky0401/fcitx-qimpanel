
QT       += core gui declarative

TARGET = fcitx-qimpanel-configtool

LIBS += -lfcitx-qt -lfcitx-config -lfcitx-utils

CONFIG += xml


SOURCES += \
    candidate_word.cpp \
    kimpanelagent.cpp \
    main.cpp \
    main_controller.cpp \
    main_model.cpp \
    my_action.cpp \
    system_tray_menu.cpp \
    toplevel.cpp \
    skin/skinbase.cpp \
    skin/skinfcitx.cpp \
    skin/skinmenu.cpp \
    skin/skinsogou.cpp

HEADERS += \
    candidate_word.h \
    config.h.in \
    kimpanelagent.h \
    kimpanelagenttype.h \
    main.h \
    main_controller.h \
    main_model.h \
    my_action.h \
    system_tray_menu.h \
    toplevel.h \
    skin/skinbase.h \
    skin/skinfcitx.h \
    skin/skinmenu.h \
    skin/skinsogou.h

OTHER_FILES += \
    .gitignore \
    CMakeLists.txt \
    fcitx.pro.user \
    fcitx-qimpanel.pro.user \
    org.kde.impanel.xml \
    README \
    TODO \
    qml/main.qml \
    qml/sogou.qml

RESOURCES += \
    qml.qrc
