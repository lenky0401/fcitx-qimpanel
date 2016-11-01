project(fcitx-qimpanel)
cmake_minimum_required(VERSION 2.8.6)
option(QT_5 "This is a option for QT_5" OFF)
option(QT_4 "This is a option for QT_4" ON)
SET(CMAKE_C_FLAGS "-std=c++11 -g -O0 -DPREFIX='\"${CMAKE_INSTALL_PREFIX}\"' ${CMAKE_C_FLAGS} ${HARDENED_C_FLAGS}")
SET(CMAKE_CXX_FLAGS "-std=c++11 -g -O0 -DPREFIX='\"${CMAKE_INSTALL_PREFIX}\"' ${CMAKE_CXX_FLAGS} ${HARDENED_C_FLAGS}")
if(QT_5)
    find_package(Fcitx 4.2.7 REQUIRED)
    find_package(Qt5DBus REQUIRED)
    find_package(Qt5LinguistTools REQUIRED)
    find_package(Qt5Quick REQUIRED)
    find_package(Qt5QuickWidgets REQUIRED)
    find_package(Qt5Widgets REQUIRED)

    include_directories(
        ${Qt5DBus_INCLUDE_DIRS}
        ${Qt5Quick_INCLUDE_DIRS}
        ${Qt5QuickWidgets_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR})

    configure_file(${PROJECT_SOURCE_DIR}/config_qt5.h.in ${PROJECT_BINARY_DIR}/config.h)

    SET(fcitx-qimpanel_RCCS qml.qrc)
    set(fcitx-qimpanel_SRCS main.cpp main_controller.cpp toplevel.cpp
        main_model.cpp kimpanelagent.cpp candidate_word.cpp system_tray_menu.cpp
        my_action.cpp skin/skinbase.cpp skin/skinfcitx.cpp)
    QT5_ADD_DBUS_ADAPTOR(fcitx-qimpanel_SRCS
        org.kde.impanel.xml
        kimpanelagent.h
        PanelAgent)

    QT5_ADD_RESOURCES(fcitx-qimpanel_RCC_SRCS ${fcitx-qimpanel_RCCS})

    add_executable(fcitx-qimpanel ${fcitx-qimpanel_SRCS} ${fcitx-qimpanel_RCC_SRCS})
    set_target_properties(fcitx-qimpanel PROPERTIES AUTOMOC TRUE)
    target_link_libraries(
        fcitx-qimpanel
        fcitx-config
        fcitx-utils
        ${Qt5DBus_LIBRARIES}
        ${Qt5Quick_LIBRARIES}
        ${Qt5QuickWidgets_LIBRARIES}
        ${Qt5Widgets_LIBRARIES})
endif()
if(QT_4)
    find_package(Fcitx 4.2.7 REQUIRED)
    find_package(Qt4 REQUIRED)

    configure_file(${PROJECT_SOURCE_DIR}/config_qt4.h.in ${PROJECT_BINARY_DIR}/config.h)

    include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR})

    SET(fcitx-qimpanel_RCCS qml.qrc)
    set(fcitx-qimpanel_SRCS main.cpp main_controller.cpp toplevel.cpp
        main_model.cpp kimpanelagent.cpp candidate_word.cpp system_tray_menu.cpp
        my_action.cpp skin/skinbase.cpp skin/skinfcitx.cpp)
    QT4_ADD_DBUS_ADAPTOR(fcitx-qimpanel_SRCS
        org.kde.impanel.xml
        kimpanelagent.h
        PanelAgent)

    QT4_ADD_RESOURCES(fcitx-qimpanel_RCC_SRCS ${fcitx-qimpanel_RCCS})

    add_executable(fcitx-qimpanel ${fcitx-qimpanel_SRCS} ${fcitx-qimpanel_RCC_SRCS})
    set_target_properties(fcitx-qimpanel PROPERTIES AUTOMOC TRUE)
    target_link_libraries(fcitx-qimpanel fcitx-config fcitx-utils
        ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY}
        ${QT_QTDBUS_LIBRARY} ${QT_QTDECLARATIVE_LIBRARY})
endif()

    set(pkgbindir       ${CMAKE_INSTALL_PREFIX}/bin)
    set(pkgdatadir      ${CMAKE_INSTALL_PREFIX}/share/fcitx-qimpanel)
    install(TARGETS fcitx-qimpanel RUNTIME DESTINATION ${pkgbindir})

    add_subdirectory(ubuntu-default-skin)
    add_subdirectory(config-tool)
    add_subdirectory(po)
