fcitx-qimpanel-configtool

How to Just Only Install fcitx-qimpanel-configtool in ubuntu:

  mkdir build; cd build
  sudo apt-get install build-essential
  sudo apt-get install fcitx-libs-dev
  sudo apt-get install libqt4-declarative libqt4-dev libqt4-dev-bin qt4-default qt4-dev-tools qt4-qmake
  qmake ../
  make
  sudo make install
  
or

  mkdir build; cd build
  sudo apt-get install cmake
  sudo apt-get install build-essential
  sudo apt-get install fcitx-libs-dev
  sudo apt-get install libqt4-declarative libqt4-dev libqt4-dev-bin qt4-default qt4-dev-tools  qt4-qmake
  cmake ../
  make
  sudo make install
  
========================
A qt4.8 based configurae tool for fcitx-qimpanel.

This is a qt-creator project.
