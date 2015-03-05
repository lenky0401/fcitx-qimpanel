fcitx-qimpanel-configtool

How to Just Only Install fcitx-qimpanel-configtool in ubuntu:

  mkdir build; cd build
  sudo apt-get install build-essential
  sudo apt-get install fcitx-libs-dev
  sudo apt-get install qtbase5-dev qtdeclarative5-dev qttools5-dev-tools
  qmake ../
  make
  sudo make install
  
or

  mkdir build; cd build
  sudo apt-get install cmake
  sudo apt-get install build-essential
  sudo apt-get install fcitx-libs-dev
  sudo apt-get install qtbase5-dev qtdeclarative5-dev qttools5-dev-tools
  cmake ../
  make
  sudo make install
  
========================
A Qt5-based configuration tool for fcitx-qimpanel.

This is a qt-creator project.
