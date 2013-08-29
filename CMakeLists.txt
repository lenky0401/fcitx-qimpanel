project(fcitx-qimpanel)
cmake_minimum_required(VERSION 2.8.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR})

SET(fcitx-qimpanel_RCCS qml.qrc)
set(fcitx-qimpanel_SRCS main.cpp main_controller.cpp toplevel.cpp
    main_model.cpp kimpanelagent.cpp candidate_word.cpp system_tray_menu.cpp)
QT4_ADD_DBUS_ADAPTOR(fcitx-qimpanel_SRCS
    org.kde.impanel.xml
    kimpanelagent.h
    PanelAgent)
QT4_ADD_RESOURCES(fcitx-qimpanel_RCC_SRCS ${fcitx-qimpanel_RCCS})

add_executable(fcitx-qimpanel ${fcitx-qimpanel_SRCS} ${fcitx-qimpanel_RCC_SRCS})
set_target_properties(fcitx-qimpanel PROPERTIES AUTOMOC TRUE)
target_link_libraries(fcitx-qimpanel ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} 
    ${QT_QTDBUS_LIBRARY} ${QT_QTDECLARATIVE_LIBRARY})
target_link_libraries(fcitx-qimpanel fcitx-utils fcitx-qt)
install(TARGETS fcitx-qimpanel RUNTIME DESTINATION bin)
