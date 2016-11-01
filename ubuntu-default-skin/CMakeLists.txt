
set(pkgbindir   ${CMAKE_INSTALL_PREFIX}/bin)
set(pkgdatadir  ${CMAKE_INSTALL_PREFIX}/share/fcitx-qimpanel)

foreach(skin ubuntu-grey ubuntu-milk ubuntu-orange)
    install(DIRECTORY ${skin} DESTINATION ${pkgdatadir}/skin)
endforeach(skin ubuntu-orange)

