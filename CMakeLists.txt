project(fcitx-qimpanel)
cmake_minimum_required(VERSION 2.8.6)

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

SET(fcitx-qimpanel_TRANS po/zh_CN.ts)
SET(fcitx-qimpanel_RCCS qml.qrc)
set(fcitx-qimpanel_SRCS main.cpp main_controller.cpp toplevel.cpp
    main_model.cpp kimpanelagent.cpp candidate_word.cpp system_tray_menu.cpp 
    my_action.cpp skin/skinmenu.cpp skin/skinbase.cpp skin/skinfcitx.cpp)
QT5_ADD_DBUS_ADAPTOR(fcitx-qimpanel_SRCS
    org.kde.impanel.xml
    kimpanelagent.h
    PanelAgent)
QT5_ADD_TRANSLATION(fcitx-qimpanel_TRAN_SRCS ${fcitx-qimpanel_TRANS})
QT5_ADD_RESOURCES(fcitx-qimpanel_RCC_SRCS ${fcitx-qimpanel_RCCS})

configure_file(${PROJECT_SOURCE_DIR}/config.h.in ${PROJECT_BINARY_DIR}/config.h)

add_executable(fcitx-qimpanel ${fcitx-qimpanel_SRCS} ${fcitx-qimpanel_TRAN_SRCS}
    ${fcitx-qimpanel_RCC_SRCS})
set_target_properties(fcitx-qimpanel PROPERTIES AUTOMOC TRUE)
target_link_libraries(
    fcitx-qimpanel
    fcitx-config
    fcitx-utils
    ${Qt5DBus_LIBRARIES}
    ${Qt5Quick_LIBRARIES}
    ${Qt5QuickWidgets_LIBRARIES}
    ${Qt5Widgets_LIBRARIES})

set(pkgbindir 	/usr/bin/)
set(pkgdatadir 	/usr/share/fcitx-qimpanel)
install(TARGETS fcitx-qimpanel RUNTIME DESTINATION ${pkgbindir})
install(FILES ${fcitx-qimpanel_TRAN_SRCS} DESTINATION ${pkgdatadir})

add_subdirectory(uk-default-skin)
add_subdirectory(config-tool)
