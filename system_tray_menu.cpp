#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "fcitx-utils/utils.h"
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

    this->addAction(QIcon::fromTheme("system-restart"),
        tr("Restart"), this, SLOT(clickSystemRestart()));
}

void SystemTrayMenu::clickOnlineHelp()
{
    QDesktopServices::openUrl(QUrl("http://fcitx-im.org/"));
}

void SystemTrayMenu::clickSystemRestart()
{
    fcitx_utils_launch_tool("fcitx-qimpanel", "-r");
    fcitx_utils_launch_restart();
}


