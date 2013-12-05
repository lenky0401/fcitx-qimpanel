
set(pkgbindir 	/usr/bin/)
set(pkgdatadir 	/usr/share/fcitx-qimpanel)

foreach(skin ubuntukylin-dark1 ubuntukylin-dark2 ubuntukylin-light1 ubuntukylin-light2)
    install(DIRECTORY ${skin} DESTINATION ${pkgdatadir}/skin)
endforeach(skin default classic dark)

