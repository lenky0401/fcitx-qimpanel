#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "system_tray_menu.h"

SystemTrayMenu::SystemTrayMenu(PanelAgent *agent)
    : QMenu()
{
    mAgent = agent;
}

SystemTrayMenu::~SystemTrayMenu()
{
    delete mIMListMenu;
    //delete mSkinMenu;
}

void SystemTrayMenu::init()
{
    mIMListMenu = new QMenu(tr("Input Method"), this);
    //mSkinMenu = new QMenu(tr("Skin"), this);

    QObject::connect(mIMListMenu, SIGNAL(aboutToShow()), this,
        SLOT(triggerUpdateIMListMenu()));

    QObject::connect(this, SIGNAL(aboutToShow()), this,
        SLOT(triggerUpdateMainMenu()));
    QObject::connect(this, SIGNAL(triggered(QAction*)), this,
        SLOT(menuItemOnClick(QAction *)));

    QObject::connect(mAgent, SIGNAL(execMenu(const QList<KimpanelProperty>)),
        this, SLOT(execMenu(const QList<KimpanelProperty>)));

}

void SystemTrayMenu::triggerUpdateMainMenu()
{
    this->clear();

    this->addAction(QIcon::fromTheme("help-contents"), tr("Online &Help!"));
    this->addSeparator();

    this->addMenu(mIMListMenu);
    //this->addMenu(mSkinMenu);
    this->addSeparator();

    this->addAction(QIcon::fromTheme("preferences-desktop"), tr("Configure"));
    this->addSeparator();

    this->addAction(QIcon::fromTheme("view-refresh"), tr("Restart"));
    this->addAction(QIcon::fromTheme("application-exit"), tr("Exit"));
}

void SystemTrayMenu::triggerUpdateIMListMenu()
{
    execMenuType = updateIMListMenu;
    QString key = "/Fcitx/im";
    mAgent->triggerProperty(key);
}

void SystemTrayMenu::setCurtIMLabel(QString label)
{
    this->curtIMLabel = label;
}

void SystemTrayMenu::doUpdateIMListMenu(const QList<KimpanelProperty> &prop_list)
{
    QAction *menu;
    QList<KimpanelProperty>::const_iterator iter;

    mIMListMenu->clear();
    for (iter = prop_list.begin(); iter != prop_list.end(); ++ iter) {
        menu = mIMListMenu->addAction(iter->label);
        menu->setCheckable(true);
        if (iter->label == this->curtIMLabel)
            menu->setChecked(true);
    }
}

void SystemTrayMenu::execMenu(const QList<KimpanelProperty> &prop_list)
{
    QList<KimpanelProperty>::const_iterator iter;

    switch (execMenuType) {
    case updateIMListMenu:
        doUpdateIMListMenu(prop_list);
        break;
    //case updateSkinMenu:
    //    tmpMenu = mSkinMenu;
    //    break;
    default:
        for (iter = prop_list.begin(); iter != prop_list.end(); ++ iter) {
            qDebug() << QString("execMenuCallback(1:%1 2:%2 3:%3 4:%4 5:%5)").arg(iter->key)
                .arg(iter->label).arg(iter->icon).arg(iter->tip).arg(iter->state);
        }
        return;
    }
}

void SystemTrayMenu::menuItemOnClick(QAction* action)
{
    if (tr("Online &Help!") == action->text()) {
        QDesktopServices::openUrl(QUrl("http://fcitx-im.org/"));

    } else if (tr("Configure") == action->text()) {
        mAgent->configure();

    } else if (tr("Restart") == action->text()) {
        mAgent->restart();

    } else if (tr("Exit") == action->text()) {
        mAgent->exit();
        exit(0);
    }
}
