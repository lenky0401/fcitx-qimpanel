/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  lenky gao    lenky0401@gmail.com/gaoqunkai@ubuntukylin.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "my_action.h"
#include "system_tray_menu.h"

SystemTrayMenu::SystemTrayMenu(PanelAgent *agent)
    : QMenu()
{
    mAgent = agent;
}

SystemTrayMenu::~SystemTrayMenu()
{
    delete mVKListMenu;
    delete mIMListMenu;
    delete mSkinMenu;
}

void SystemTrayMenu::init()
{
    mVKListMenu = new QMenu(tr("Virtual Keyboard"), this);
    mIMListMenu = new QMenu(tr("Input Method"), this);
    mSkinMenu = new SkinMenu(tr("Skin"), this);

    QObject::connect(mVKListMenu, SIGNAL(aboutToShow()), this,
        SLOT(triggerUpdateVKListMenu()));

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
    mStatusMenuList.clear();
    foreach(const KimpanelProperty &prop, props) {
        //qDebug() << QString("triggerUpdateMainMenu(1:%1 2:%2 3:%3 4:%4 5:%5 6:%6)").arg(prop.key)
        //    .arg(prop.label).arg(prop.icon).arg(prop.tip).arg(prop.state).arg(prop.menu);
        if (count ++ < StatusMenuSkip)
            continue;
        if (prop.key == "/Fcitx/vk")
            continue;
        this->mStatusMenuList << prop;
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
    MyAction *menu;
    this->clear();

    this->addAction(QIcon::fromTheme("help-contents"), tr("Online &Help!"));
    this->addSeparator();

    foreach(const KimpanelProperty &prop, this->mStatusMenuList) {
        menu = new MyAction(QIcon::fromTheme(prop.icon), prop.label, this);
        menu->setProp(prop);
        this->addAction(menu);
    }
    this->addSeparator();

    this->addMenu(mVKListMenu);
    this->addMenu(mIMListMenu);
    this->addMenu(mSkinMenu);
    this->addSeparator();

    this->addAction(QIcon::fromTheme("preferences-desktop"), tr("ConfigureIM"));
    this->addAction(QIcon::fromTheme("preferences-desktop"), tr("Configure"));
    this->addSeparator();

    this->addAction(QIcon::fromTheme("view-refresh"), tr("Restart"));
    this->addAction(QIcon::fromTheme("application-exit"), tr("Exit"));
}

void SystemTrayMenu::triggerUpdateVKListMenu()
{
    mExecMenuType = updateVKListMenu;
    mAgent->triggerProperty(QString("/Fcitx/vk"));
}

void SystemTrayMenu::triggerUpdateIMListMenu()
{
    mExecMenuType = updateIMListMenu;
    mAgent->triggerProperty(QString("/Fcitx/im"));
}

void SystemTrayMenu::doUpdateVKListMenu(const QList<KimpanelProperty> &prop_list)
{
    MyAction *menu;
    QList<KimpanelProperty>::const_iterator iter;

    mVKListMenu->clear();
    for (iter = prop_list.begin(); iter != prop_list.end(); ++ iter) {
        menu = new MyAction(QIcon::fromTheme(iter->icon), iter->label, this);
        menu->setProp(*iter);
        mVKListMenu->addAction(menu);
    }
}

void SystemTrayMenu::doUpdateIMListMenu(const QList<KimpanelProperty> &prop_list)
{
    bool checked = false;
    MyAction *firstMenu = NULL, *menu;
    QList<KimpanelProperty>::const_iterator iter;

    mIMListMenu->clear();
    for (iter = prop_list.begin(); iter != prop_list.end(); ++ iter) {
        menu = new MyAction(QIcon::fromTheme(iter->icon), iter->label, this);
        menu->setProp(*iter);
        mIMListMenu->addAction(menu);
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
    case updateVKListMenu:
        doUpdateVKListMenu(prop_list);
        break;
    case updateIMListMenu:
        doUpdateIMListMenu(prop_list);
        break;
    //case updateThemerMenu:
    //    tmpMenu = mSkinMenu;
    //    break;
    default:
        for (iter = prop_list.begin(); iter != prop_list.end(); ++ iter) {
            qDebug() << QString("execMenuCallback(1:%1 2:%2 3:%3 4:%4 5:%5 6:%6)").arg(iter->key)
                .arg(iter->label).arg(iter->icon).arg(iter->tip).arg(iter->state).arg(iter->menu);
        }
        break;
    }

    mExecMenuType = nullExecMenuType;
}

void SystemTrayMenu::restart()
{
    /* exec command */
    pid_t child_pid;

    child_pid = fork();
    if (child_pid < 0) {
        perror("fork");
    } else if (child_pid == 0) {         /* child process  */
        pid_t grandchild_pid;

        grandchild_pid = fork();
        if (grandchild_pid < 0) {
            perror("fork");
            _exit(1);
        } else if (grandchild_pid == 0) { /* grandchild process  */
            execvp("fcitx-qimpanel", NULL);
            perror("execvp");
            _exit(1);
        } else {
            _exit(0);
        }
    } else {                              /* parent process */
        int status;
        waitpid(child_pid, &status, 0);
        _exit(0);
    }
}


void SystemTrayMenu::menuItemOnClick(QAction *action)
{
    if (tr("Online &Help!") == action->text()) {
        QDesktopServices::openUrl(QUrl("http://fcitx-im.org/"));

    } else if (tr("ConfigureIM") == action->text()) {
        mAgent->triggerProperty(QString("/Fcitx/logo/configureim"));

    } else if (tr("Configure") == action->text()) {
        mAgent->configure();

    } else if (tr("Restart") == action->text()) {
        mAgent->restart();
        this->restart();

    } else if (tr("Exit") == action->text()) {
        mAgent->exit();
        exit(0);
    } else {
        MyAction *myAction = (MyAction *)action;
        if (myAction->getProp().key != "") {
            mAgent->triggerProperty(myAction->getProp().key);
        }
    }
}
