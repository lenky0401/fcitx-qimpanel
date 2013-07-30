project(fcitx-kimpanel)
cmake_minimum_required(VERSION 2.8.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR})

SET(fcitx-kimpanel_RCCS qml.qrc)
set(fcitx-kimpanel_SRCS main.cpp main_controller.cpp 
    main_model.cpp kimpanelagent.cpp candidate_word.cpp system_tray_menu.cpp)
QT4_ADD_DBUS_ADAPTOR(fcitx-kimpanel_SRCS
    org.kde.impanel.xml
    kimpanelagent.h
    PanelAgent)
QT4_ADD_RESOURCES(fcitx-kimpanel_RCC_SRCS ${fcitx-kimpanel_RCCS})

add_executable(fcitx-kimpanel ${fcitx-kimpanel_SRCS} ${fcitx-kimpanel_RCC_SRCS})
set_target_properties(fcitx-kimpanel PROPERTIES AUTOMOC TRUE)
target_link_libraries(fcitx-kimpanel ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} 
    ${QT_QTDBUS_LIBRARY} ${QT_QTDECLARATIVE_LIBRARY})
install(TARGETS fcitx-kimpanel RUNTIME DESTINATION bin)
