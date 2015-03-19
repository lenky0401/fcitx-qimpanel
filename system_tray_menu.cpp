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
#include <QDir>
#include <QString>
#include <QMessageBox>
#include <QSettings>
#include <libintl.h>

#include "main.h"
#include "my_action.h"
#include "system_tray_menu.h"
#include "config.h"

SystemTrayMenu::SystemTrayMenu(PanelAgent *agent)
    : QMenu()
{
    mAgent = agent;
}

SystemTrayMenu::~SystemTrayMenu()
{

}

void SystemTrayMenu::init()
{

    QObject::connect(this, SIGNAL(aboutToShow()), this,
        SLOT(triggerUpdateVKListMenu()));

    QObject::connect(this, SIGNAL(aboutToShow()), this,
        SLOT(triggerUpdateIMListMenu()));

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
        //qDebug() << QString("registerProperties(1:%1 2:%2 3:%3 4:%4 5:%5 6:%6)").arg(prop.key)
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
    if (gettext("No input window") == prop.label)
        return;

    this->mCurtIMLabel = prop.label;
}

void SystemTrayMenu::updateMainMenu()
{
    MyAction *menu;
    this->clear();

    this->addAction(QIcon::fromTheme("help-contents"), gettext("Online &Help!"));
    this->addSeparator();

    bool kbd = this->doUpdateIMListMenu(mIMList);
    this->addSeparator();

    if (kbd)
    {
        this->doUpdateVKListMenu(mVKList);
        this->addSeparator();
    }

    foreach(const KimpanelProperty &prop, this->mStatusMenuList) {
           menu = new MyAction(QIcon::fromTheme(prop.icon), prop.label, this);
           menu->setProp(prop);
           this->addAction(menu);
    }
    this->addSeparator();

    this->addAction(QIcon::fromTheme("preferences-desktop"), gettext("ConfigureFcitx"));
    this->addAction(QIcon::fromTheme("preferences-desktop"), gettext("ConfigureIMPanel"));

    if (isUnity()) {
        this->addSeparator();
        this->addAction(gettext("Character Map"));
        this->addAction(gettext("Keyboard Layout Chart"));
        this->addAction(gettext("Text Entry Settings..."));
        this->addSeparator();
    }
}

void SystemTrayMenu::triggerUpdateVKListMenu()
{
    mAgent->triggerProperty(QString("/Fcitx/vk"));
}

void SystemTrayMenu::triggerUpdateIMListMenu()
{
    mAgent->triggerProperty(QString("/Fcitx/im"));
}

void SystemTrayMenu::doUpdateVKListMenu(const QList<KimpanelProperty> &prop_list)
{
    MyAction *menu;
    QList<KimpanelProperty>::const_iterator iter;

    for (iter = prop_list.begin(); iter != prop_list.end(); ++ iter) {
        menu = new MyAction(QIcon::fromTheme(iter->icon), iter->label, this);
        menu->setProp(*iter);
        this->addAction(menu);
    }
}

bool SystemTrayMenu::doUpdateIMListMenu(const QList<KimpanelProperty> &prop_list)
{
    bool checked = false;
    MyAction *firstAction = NULL, *action = NULL, *actionChecked = NULL;
    QList<KimpanelProperty>::const_iterator iter;

    for (iter = prop_list.begin(); iter != prop_list.end(); ++ iter) {
        if(iter->icon=="fcitx-kbd" || iter->icon==""||iter->icon.indexOf("indicator-keyboard")!=-1)
            action = new MyAction(QIcon::fromTheme("fcitx-kbd"), iter->label, this);
        else
            action = new MyAction(QIcon::fromTheme(iter->icon), iter->label, this);
        action->setProp(*iter);
        this->addAction(action);
        if (firstAction == NULL)
            firstAction = action;
        action->setCheckable(true);
        if (iter->label == this->mCurtIMLabel) {
            checked = true;
            actionChecked = action;
            action->setChecked(true);
        }
    }

    if (!checked && firstAction)
    {
        actionChecked = firstAction;
        firstAction->setChecked(true);
    }

    if (actionChecked == NULL)
        return false;
    else
        return actionChecked->icon().name() == "fcitx-kbd";
}

bool SystemTrayMenu::isIMList(const QString &key)
{
    return key.startsWith("/Fcitx/im");
}

bool SystemTrayMenu::isVKList(const QString &key)
{
    return key.startsWith("/Fcitx/vk");
}

void SystemTrayMenu::execMenu(const QList<KimpanelProperty> &prop_list)
{
    QList<KimpanelProperty>::const_iterator iter = prop_list.begin();
    if (isIMList(iter->key))
        mIMList = prop_list;
    else if (isVKList(iter->key))
        mVKList = prop_list;
    else {
        for (iter = prop_list.begin(); iter != prop_list.end(); ++ iter) {
            qDebug() << QString("execMenuCallback(1:%1 2:%2 3:%3 4:%4 5:%5 6:%6)").arg(iter->key)
                .arg(iter->label).arg(iter->icon).arg(iter->tip).arg(iter->state).arg(iter->menu);
        }
    }

    updateMainMenu();
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
            char *argv_exec[] = {(char *)"fcitx-qimpanel", NULL};
            execvp("fcitx-qimpanel", argv_exec);
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

void SystemTrayMenu::startChildApp(const char *app_exe, const char * const argv[])
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
            execvp(app_exe, const_cast<char * const *>(argv));
            perror("execvp");
            _exit(1);
        } else {
            _exit(0);
        }
    }
}

void SystemTrayMenu::menuItemOnClick(QAction *action)
{
    if (gettext("Online &Help!") == action->text()) {
        QDesktopServices::openUrl(QUrl("http://fcitx-im.org/"));

    } else if (gettext("ConfigureIM") == action->text()) {
        mAgent->triggerProperty(QString("/Fcitx/logo/configureim"));

    } else if (gettext("ConfigureIMPanel") == action->text()) {

        QFile toolFile(getQimpanelBinPath("fcitx-qimpanel-configtool"));
        if (!toolFile.exists()) {
            QMessageBox::warning(this,gettext("Warning"),gettext("Please install fcitx-qimpanel-configtool!"));
        }
        startChildApp("fcitx-qimpanel-configtool");

    } else if (gettext("ConfigureFcitx") == action->text()) {
        mAgent->configure();

    } else if (gettext("Restart") == action->text()) {
        mAgent->restart();
        this->restart();

    } else if (gettext("Exit") == action->text()) {
        mAgent->exit();
        exit(0);
    } else if (gettext("Character Map") == action->text()) {
        startChildApp("gucharmap");
    } else if (gettext("Keyboard Layout Chart") == action->text()) {
        const char *argv[4] = { "gkbd-keyboard-display", "-l", NULL, NULL };

        QString layout = "us";
        QList<KimpanelProperty>::const_iterator i;
        for (i = mIMList.begin(); i != mIMList.end(); ++i) {
            if (i->label == mCurtIMLabel) {
                if (i->key.startsWith("/Fcitx/im/fcitx-keyboard-")) {
                    layout = i->key.mid(strlen("/Fcitx/im/fcitx-keyboard-"));
                }
                break;
            }
        }
        QByteArray bytes = layout.toLatin1();
        int separator = bytes.indexOf('-');
        if (separator != -1)
            bytes[separator] = '\t';
        argv[2] = bytes.constData();

        startChildApp("gkbd-keyboard-display", argv);
    } else if (gettext("Text Entry Settings...") == action->text()) {
        const char *argv[4] = { "unity-control-center", "region", "layouts", NULL };
        startChildApp("unity-control-center", argv);
    } else {
        MyAction *myAction = (MyAction *)action;
        if (myAction->getProp().key != "") {
            mAgent->triggerProperty(myAction->getProp().key);
        }
    }
}

bool SystemTrayMenu::isUnity()
{
    const char *desktop = getenv("XDG_CURRENT_DESKTOP");
    return desktop && !strcmp(desktop, "Unity");
}

