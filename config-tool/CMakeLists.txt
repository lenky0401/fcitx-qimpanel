project(fcitx-qimpanel-configtool)
cmake_minimum_required(VERSION 2.8.6)

find_package(Fcitx 4.2.7 REQUIRED)
find_package(Qt5DBus REQUIRED)
find_package(Qt5LinguistTools REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5QuickWidgets REQUIRED)

include_directories(BEFORE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR})

SET(fcitx-qimpanel-configtool_TRANS po/fcitx_skin_zh_CN.ts)
SET(fcitx-qimpanel-configtool_RCCS main.qrc)

set(fcitx-qimpanel-configtool_SRCS main.cpp 
    mainwindow.cpp 
    main_model.cpp
    candidate_word.cpp
    editingskindialog.cpp
    skin/skinbase.cpp
    skin/skinfcitx.cpp    
    )
set(fcitx-qimpanel-configtool_FORMS mainwindow.ui
    editingskindialog.ui
    )

QT5_ADD_TRANSLATION(fcitx-qimpanel-configtool_TRAN_SRCS ${fcitx-qimpanel-configtool_TRANS})
QT5_ADD_RESOURCES(fcitx-qimpanel-configtool_RCC_SRCS ${fcitx-qimpanel-configtool_RCCS})
QT5_WRAP_UI(helloworld_FORMS_HEADERS ${fcitx-qimpanel-configtool_FORMS})

add_executable(fcitx-qimpanel-configtool ${fcitx-qimpanel-configtool_SRCS} ${fcitx-qimpanel-configtool_TRAN_SRCS}
    ${fcitx-qimpanel-configtool_RCC_SRCS} ${fcitx-qimpanel-configtool_FORMS})
set_target_properties(fcitx-qimpanel-configtool PROPERTIES AUTOMOC TRUE)

target_link_libraries(
    fcitx-qimpanel-configtool
    fcitx-utils
    ${Qt5DBus_LIBRARIES}
    ${Qt5Quick_LIBRARIES}
    ${Qt5QuickWidgets_LIBRARIES})
install(FILES fcitx_ubuntukylin.png DESTINATION /usr/share/pixmaps)
install(FILES fcitx-qimpanel-configtool.desktop DESTINATION /usr/share/applications)
set(pkgbindir 	/usr/bin/)
set(pkgdatadir 	/usr/share/fcitx-qimpanel)
install(TARGETS fcitx-qimpanel-configtool RUNTIME DESTINATION ${pkgbindir})
install(FILES ${fcitx-qimpanel-configtool_TRAN_SRCS} DESTINATION ${pkgdatadir})

