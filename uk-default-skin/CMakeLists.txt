
set(package     fcitx)
set(prefix      ${CMAKE_INSTALL_PREFIX})
set(pkgdatadir ${prefix}/share/${package})

foreach(skin ubuntukylin-dark1 ubuntukylin-dark2 ubuntukylin-light1 ubuntukylin-light2)
    install(DIRECTORY ${skin} DESTINATION ${pkgdatadir}/skin)
endforeach(skin default classic dark)

