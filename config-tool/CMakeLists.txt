project(fcitx-qimpanel-configtool)
cmake_minimum_required(VERSION 2.8.6)
option(QT_5 "This is a option for QT_5" ON)
option(QT_4 "This is a option for QT_4" OFF)
SET(CMAKE_C_FLAGS "-DPREFIX='\"${CMAKE_INSTALL_PREFIX}\"' ${CMAKE_C_FLAGS}")
SET(CMAKE_CXX_FLAGS "-DPREFIX='\"${CMAKE_INSTALL_PREFIX}\"' ${CMAKE_CXX_FLAGS}")
find_package(Fcitx 4.2.7 REQUIRED)
if(QT_5)
    find_package(Qt5DBus REQUIRED)
    find_package(Qt5LinguistTools REQUIRED)
    find_package(Qt5Quick REQUIRED)
    find_package(Qt5QuickWidgets REQUIRED)

    configure_file(${PROJECT_SOURCE_DIR}/config_qt5.h.in ${PROJECT_BINARY_DIR}/config.h)

    include_directories(BEFORE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR})

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

    QT5_ADD_RESOURCES(fcitx-qimpanel-configtool_RCC_SRCS ${fcitx-qimpanel-configtool_RCCS})
    QT5_WRAP_UI(helloworld_FORMS_HEADERS ${fcitx-qimpanel-configtool_FORMS})

    add_executable(fcitx-qimpanel-configtool ${fcitx-qimpanel-configtool_SRCS} ${fcitx-qimpanel-configtool_RCC_SRCS} ${fcitx-qimpanel-configtool_FORMS})
    set_target_properties(fcitx-qimpanel-configtool PROPERTIES AUTOMOC TRUE)

    target_link_libraries(
        fcitx-qimpanel-configtool
        fcitx-utils
        ${Qt5DBus_LIBRARIES}
        ${Qt5Quick_LIBRARIES}
        ${Qt5QuickWidgets_LIBRARIES})

endif()
if(QT_4)
    find_package(Qt4 REQUIRED)

    configure_file(${PROJECT_SOURCE_DIR}/config_qt4.h.in ${PROJECT_BINARY_DIR}/config.h)

    include_directories(BEFORE ${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR})

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

    QT4_ADD_RESOURCES(fcitx-qimpanel-configtool_RCC_SRCS ${fcitx-qimpanel-configtool_RCCS})
    QT4_WRAP_UI(helloworld_FORMS_HEADERS ${fcitx-qimpanel-configtool_FORMS})

    add_executable(fcitx-qimpanel-configtool ${fcitx-qimpanel-configtool_SRCS} ${fcitx-qimpanel-configtool_RCC_SRCS} ${fcitx-qimpanel-configtool_FORMS})
    set_target_properties(fcitx-qimpanel-configtool PROPERTIES AUTOMOC TRUE)

    target_link_libraries(fcitx-qimpanel-configtool fcitx-utils
        ${QT_QTCORE_LIBRARY}
        ${QT_QTGUI_LIBRARY}
        ${QT_QTDBUS_LIBRARY}
        ${QT_QTDECLARATIVE_LIBRARY}
        #${QT_QTNETWORK_LIBRARY}
        )
endif()
    install(FILES fcitx_ubuntukylin.png DESTINATION ${CMAKE_INSTALL_PREFIX}/share/pixmaps)
    install(FILES fcitx-qimpanel-configtool.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
    set(pkgbindir       ${CMAKE_INSTALL_PREFIX}/bin)
    set(pkgdatadir      ${CMAKE_INSTALL_PREFIX}/share/fcitx-qimpanel)
    install(TARGETS fcitx-qimpanel-configtool RUNTIME DESTINATION ${pkgbindir})
