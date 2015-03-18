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

#ifdef ENABLE_UK_SYNC
#define UBUNTU_KYLIN_SYNC "/[Ubuntu\\ Kylin\\ Sync]/"

#define UBUNTU_KYLIN_SYNC_M "/[Ubuntu Kylin Sync]/"
#endif

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
#ifdef ENABLE_UK_SYNC
    delete mSyncMenu;
#endif
}

void SystemTrayMenu::init()
{
    mVKListMenu = new QMenu(gettext("Virtual Keyboard"), this);
    mIMListMenu = new QMenu(gettext("Input Method"), this);
#ifdef ENABLE_UK_SYNC
    mSyncMenu = new QMenu(gettext("ConfigureSync"),this);
#endif
    mSkinMenu = new SkinMenu(gettext("Skin"), this);

    QObject::connect(mVKListMenu, SIGNAL(aboutToShow()), this,
        SLOT(triggerUpdateVKListMenu()));

    QObject::connect(mIMListMenu, SIGNAL(aboutToShow()), this,
        SLOT(triggerUpdateIMListMenu()));

#ifdef ENABLE_UK_SYNC
    QObject::connect(mSyncMenu, SIGNAL(aboutToShow()), this,
        SLOT(triggerUpdateSyncMenu()));
#endif

    if (isUnity())
        QObject::connect(this, SIGNAL(aboutToShow()), this,
            SLOT(triggerUpdateIMListMenu()));
    else
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
    if (gettext("No input window") == prop.label)
        return;

    this->mCurtIMLabel = prop.label;
}

void SystemTrayMenu::triggerUpdateMainMenu()
{
    MyAction *menu;
    this->clear();

    this->addAction(QIcon::fromTheme("help-contents"), gettext("Online &Help!"));
    this->addSeparator();

    if (isUnity()) {
        appendIMListToMenu(this, mIMList);
        this->addSeparator();
    }

    foreach(const KimpanelProperty &prop, this->mStatusMenuList) {
           menu = new MyAction(QIcon::fromTheme(prop.icon), prop.label, this);
           menu->setProp(prop);
           this->addAction(menu);
    }
    this->addSeparator();

    this->addMenu(mVKListMenu);
    if (!isUnity())
        this->addMenu(mIMListMenu);
    this->addMenu(mSkinMenu);
    this->addSeparator();

    this->addAction(QIcon::fromTheme("preferences-desktop"), gettext("Configure"));
    this->addAction(QIcon::fromTheme("preferences-desktop"), gettext("ConfigureIMPanel"));
    this->addAction(QIcon::fromTheme("preferences-desktop"), gettext("ConfigureIM"));
#ifdef ENABLE_UK_SYNC
    this->addMenu(mSyncMenu);
#endif
    this->addSeparator();

    if (isUnity()) {
        this->addAction(gettext("Character Map"));
        this->addAction(gettext("Keyboard Layout Chart"));
        this->addAction(gettext("Text Entry Settings..."));
        this->addSeparator();
    }

    this->addAction(QIcon::fromTheme("view-refresh"), gettext("Restart"));
    this->addAction(QIcon::fromTheme("application-exit"), gettext("Exit"));
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

#ifdef ENABLE_UK_SYNC
void SystemTrayMenu::triggerUpdateSyncMenu()
{
    mSyncMenu->clear();
    mSyncMenu->addAction(QIcon::fromTheme(""), gettext("ConfigureUp"));
    mSyncMenu->addAction(QIcon::fromTheme(""), gettext("ConfigureDwon"));
}
#endif

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
    mIMListMenu->clear();
    appendIMListToMenu(mIMListMenu, prop_list);
}

void SystemTrayMenu::appendIMListToMenu(QMenu *menu, const QList<KimpanelProperty> &prop_list)
{
    bool checked = false;
    MyAction *firstAction = NULL, *action;
    QList<KimpanelProperty>::const_iterator iter;

    for (iter = prop_list.begin(); iter != prop_list.end(); ++ iter) {
        if(iter->icon=="fcitx-kbd" || iter->icon==""||iter->icon.indexOf("indicator-keyboard")!=-1)
            action = new MyAction(QIcon::fromTheme("fcitx-kbd"), iter->label, this);
        else
            action = new MyAction(QIcon::fromTheme(iter->icon), iter->label, this);
        action->setProp(*iter);
        menu->addAction(action);
        if (firstAction == NULL)
            firstAction = action;
        action->setCheckable(true);
        if (iter->label == this->mCurtIMLabel) {
            checked = true;
            action->setChecked(true);
        }
    }
    if (!checked && firstAction)
        firstAction->setChecked(true);
}

void SystemTrayMenu::execMenu(const QList<KimpanelProperty> &prop_list)
{
    QList<KimpanelProperty>::const_iterator iter;

    switch (mExecMenuType) {
    case updateVKListMenu:
        doUpdateVKListMenu(prop_list);
        break;
    case updateIMListMenu:
        if (isUnity()) {
            mIMList = prop_list;
            triggerUpdateMainMenu();
        } else {
            doUpdateIMListMenu(prop_list);
        }
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

#ifdef ENABLE_UK_SYNC
void SystemTrayMenu::syncConfigUp()
{
    qDebug()<<"SystemTrayMenu::syncConfigUp";
    QString kuaipanConfPath = qgetenv("HOME") + "/.config/ubuntukylin/";
    QString kuaipanSyncPath;
    QString fcitxQimpanelConfPath = qgetenv("HOME") +"/.config/fcitx-qimpanel/main.conf ";
    QString fcitxConfPath = qgetenv("HOME") +"/.config/fcitx/config ";
    QDir *temp = new QDir;
    QDir *temp1 = new QDir;
    if(true == temp->exists(kuaipanConfPath))
    {
       QSettings* mSettings = new QSettings(kuaipanConfPath + "kuaipan4uk.conf",QSettings::IniFormat);
       mSettings->setIniCodec("UTF-8");
       mSettings->beginGroup("client-info");
       kuaipanSyncPath = mSettings->value("Root").toString();
       mSettings->endGroup();
       if(true == temp1->exists(kuaipanSyncPath + UBUNTU_KYLIN_SYNC_M))
       {
           if(false == temp1->exists(kuaipanSyncPath + UBUNTU_KYLIN_SYNC_M"fcitx"))
           {
               QString cmd = "mkdir " + kuaipanSyncPath +UBUNTU_KYLIN_SYNC +"fcitx";
               qDebug()<<cmd;
               QByteArray ba = cmd.toLatin1();
               const char *transpd = ba.data();
               if(0!= system(transpd))
               {
                   return;
               }
           }
           //fcitx-qimpanel
           QString cmd1 = "cp " + fcitxQimpanelConfPath + kuaipanSyncPath +UBUNTU_KYLIN_SYNC"fcitx";
           qDebug()<<cmd1;
           QByteArray ba1 = cmd1.toLatin1();
           const char *transpd1 = ba1.data();
           if(0!= system(transpd1))
           {
               return;
           }
           //fcitx
           QString cmd2 = "cp " + fcitxConfPath + kuaipanSyncPath +UBUNTU_KYLIN_SYNC"fcitx";
           qDebug()<<cmd2;
           QByteArray ba2 = cmd2.toLatin1();
           const char *transpd2 = ba2.data();
           if(0!= system(transpd2))
           {
               return;
           }
        }
        else{
           QMessageBox::warning(this,gettext("Warning"),gettext("[Ubuntu Kylin Sync] Synchronize directories have been deleted?!"));
       }
    }
    else{
         QMessageBox::warning(this,gettext("Warning"),gettext("Please log in kuaipan!"));
    }
}

void SystemTrayMenu::syncConfigDown()
{
    qDebug()<<"SystemTrayMenu::syncConfigDown";
    QString kuaipanConfPath = qgetenv("HOME") + "/.config/ubuntukylin/";
    QString kuaipanSyncPath;
    QString fcitxQimpanelConfPath = qgetenv("HOME") +"/.config/fcitx-qimpanel/";
    QString fcitxConfPath = qgetenv("HOME") +"/.config/fcitx/";
    QDir *temp = new QDir;
    QDir *temp1 = new QDir;
    if(true == temp->exists(kuaipanConfPath))
    {
       QSettings* mSettings = new QSettings(kuaipanConfPath + "kuaipan4uk.conf",QSettings::IniFormat);
       mSettings->setIniCodec("UTF-8");
       mSettings->beginGroup("client-info");
       kuaipanSyncPath = mSettings->value("Root").toString();
       mSettings->endGroup();
       if(true == temp1->exists(kuaipanSyncPath + UBUNTU_KYLIN_SYNC_M))
       {
           if(false == temp1->exists(kuaipanSyncPath + UBUNTU_KYLIN_SYNC_M"fcitx"))
           {
               QMessageBox::warning(this,gettext("Warning"),gettext("No configure can be synchronized!"));
               return;
           }
           //fcitx-qimpanel
           QString cmd1 = "cp " + kuaipanSyncPath +UBUNTU_KYLIN_SYNC"fcitx/main.conf "  + fcitxQimpanelConfPath;
           QByteArray ba1 = cmd1.toLatin1();
           const char *transpd1 = ba1.data();
           if(0!= system(transpd1))
           {
               return;
           }
           //fcitx
           QString cmd2 = "cp " + kuaipanSyncPath +UBUNTU_KYLIN_SYNC"fcitx/config " + fcitxConfPath;
           QByteArray ba2 = cmd2.toLatin1();
           const char *transpd2 = ba2.data();
           if(0!= system(transpd2))
           {
               return;
           }
        }
       else{
            QMessageBox::warning(this,gettext("Warning"),gettext("[Ubuntu Kylin Sync] Synchronize directories have been deleted?!"));
       }

    }
    else{
         QMessageBox::warning(this,gettext("Warning"),gettext("Please log in kuaipan!"));
    }
}
#endif	

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

    } else if (gettext("Configure") == action->text()) {
        mAgent->configure();

    } else if (gettext("Restart") == action->text()) {
        mAgent->restart();
        this->restart();

    } else if (gettext("Exit") == action->text()) {
        mAgent->exit();
        exit(0);
#ifdef ENABLE_UK_SYNC
    } else if (gettext("ConfigureUp") == action->text()) {
        qDebug()<<"SystemTrayMenu::ConfigureUp";
        syncConfigUp();
    } else if (gettext("ConfigureDwon") == action->text()){
        qDebug()<<"SystemTrayMenu::ConfigureDown";
        syncConfigDown();
#endif		
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
