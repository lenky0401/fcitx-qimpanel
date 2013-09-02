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

    QObject::connect(mAgent, SIGNAL(registerProperties(const QList<KimpanelProperty>)),
        this, SLOT(registerProperties(const QList<KimpanelProperty>)));

    QObject::connect(mAgent, SIGNAL(updateProperty(KimpanelProperty)), this,
        SLOT(updateProperty(KimpanelProperty)));

}

void SystemTrayMenu::registerProperties(const QList<KimpanelProperty> &props)
{
    int count = 0;
    mDynamicMenuList.clear();
    foreach(const KimpanelProperty &prop, props) {
        if (count ++ < DynamicMenuSkip)
            continue;
        this->mDynamicMenuList << prop;
    }
}

void SystemTrayMenu::updateProperty(const KimpanelProperty &prop)
{
    if (tr("No input window") == prop.label)
        return;

    this->mCurtIMLabel = prop.label;
}

void SystemTrayMenu::triggerUpdateMainMenu()
{
    this->clear();

    this->addAction(QIcon::fromTheme("help-contents"), tr("Online &Help!"));
    this->addSeparator();

    foreach(const KimpanelProperty &prop, this->mDynamicMenuList) {
        //qDebug() << QString("triggerUpdateMainMenu(1:%1 2:%2 3:%3 4:%4 5:%5)").arg(prop.key)
        //    .arg(prop.label).arg(prop.icon).arg(prop.tip).arg(prop.state);
        this->addAction(QIcon::fromTheme(prop.icon), prop.label);
    }
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
    mExecMenuType = updateIMListMenu;
    mAgent->triggerProperty(QString("/Fcitx/im"));
}

void SystemTrayMenu::doUpdateIMListMenu(const QList<KimpanelProperty> &prop_list)
{
    bool checked = false;
    QAction *firstMenu = NULL, *menu;
    QList<KimpanelProperty>::const_iterator iter;

    mIMListMenu->clear();
    for (iter = prop_list.begin(); iter != prop_list.end(); ++ iter) {
        menu = mIMListMenu->addAction(iter->label);
        if (firstMenu == NULL)
            firstMenu = menu;
        menu->setCheckable(true);
        if (iter->label == this->mCurtIMLabel) {
            checked = true;
            menu->setChecked(true);
        }
    }
    if (!checked)
        firstMenu->setChecked(true);
}

void SystemTrayMenu::execMenu(const QList<KimpanelProperty> &prop_list)
{
    QList<KimpanelProperty>::const_iterator iter;

    switch (mExecMenuType) {
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
        break;
    }
    mExecMenuType = nullExecMenuType;
}

bool SystemTrayMenu::dynamicMenuItemOnClick(QAction *action)
{
    foreach(const KimpanelProperty &prop, this->mDynamicMenuList) {
        if (prop.label == action->text()) {
            mAgent->triggerProperty(prop.key);
            return true;
        }
    }
    return false;
}

void SystemTrayMenu::menuItemOnClick(QAction *action)
{
    if (dynamicMenuItemOnClick(action))
        return;

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
