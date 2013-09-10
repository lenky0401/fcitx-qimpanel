
foreach(skin ubuntukylin-dark1 ubuntukylin-dark2 ubuntukylin-light1 ubuntukylin-light2)
    install(DIRECTORY ${skin} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/uk-default-skin)
endforeach(skin default classic dark)

