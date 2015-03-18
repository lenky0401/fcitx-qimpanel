
set(pkgbindir 	/usr/bin/)
set(pkgdatadir 	/usr/share/fcitx-qimpanel)

foreach(skin ubuntu-orange)
    install(DIRECTORY ${skin} DESTINATION ${pkgdatadir}/skin)
endforeach(skin ubuntu-orange)

