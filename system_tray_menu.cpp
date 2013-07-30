#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include "system_tray_menu.h"

SystemTrayMenu::SystemTrayMenu()
    : QMenu()
{

}

SystemTrayMenu::~SystemTrayMenu()
{

}

void SystemTrayMenu::init()
{
    this->addAction(QIcon::fromTheme("help-contents"),
        tr("Online &Help!"), this, SLOT(clickOnlineHelp()));
}

void SystemTrayMenu::clickOnlineHelp()
{
    QDesktopServices::openUrl(QUrl("http://fcitx-im.org/"));
}
