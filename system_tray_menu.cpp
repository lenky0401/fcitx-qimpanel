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
#include <QProcess>
#include <fcitx-config/fcitx-config.h>
#include <stdio.h>

#include "main.h"
#include "my_action.h"
#include "main_controller.h"
#include "system_tray_menu.h"
#include "skin/skinfcitx.h"

SystemTrayMenu::SystemTrayMenu(PanelAgent *agent)
    : QMenu()
{
    mAgent = agent;
    configtoolPro= new QProcess;
}

SystemTrayMenu::~SystemTrayMenu()
{
    if(configtoolPro)
        free(configtoolPro);
    delete mVKListMenu;
    delete mSkinMenu;
    delete mMozcHiraganaMenu;
    delete mMozcToolMenu;
}

void SystemTrayMenu::init()
{
    mVKListMenu = new QMenu(gettext("Virtual Keyboard"), this);
    mSkinMenu = new QMenu(gettext("Skin"), this);
    mMozcHiraganaMenu = new QMenu(gettext("Mozc Edit mode"), this);
    mMozcToolMenu = new QMenu(gettext("Mozc Tool"), this);
    QObject::connect(this, SIGNAL(aboutToHide()), this,
        SLOT(clearMenu()));

    QObject::connect(this, SIGNAL(aboutToShow()), this,
        SLOT(triggerUpdateVKListMenu()));

    QObject::connect(this, SIGNAL(aboutToShow()), this,
        SLOT(truggerUpdateMozcHiraganaMenu()));

    QObject::connect(this, SIGNAL(aboutToShow()), this,
        SLOT(truggerUpdateMozcToolMenu()));

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
      updateMainMenu();
}

void SystemTrayMenu::registerProperties(const QList<KimpanelProperty> &props)
{
    int count = 0;
    mStatusMenuList.clear();
    foreach(const KimpanelProperty &prop, props) {
//        qDebug() << i<<QString("registerProperties(1:%1 2:%2 3:%3 4:%4 5:%5 6:%6)\n").arg(prop.key)
//            .arg(prop.label).arg(prop.icon).arg(prop.tip).arg(prop.state).arg(prop.menu);
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
void SystemTrayMenu::clearMenu()
{
    this->clear();
}

void SystemTrayMenu::updateMainMenu()
{
    this->clear();
    this->addAction(QIcon::fromTheme("help-contents"), gettext("Online &Help!"));
    this->addSeparator();

    QString currentIM = this->doUpdateIMListMenu(mIMList);
    this->addSeparator();
    if (currentIM=="fcitx-kbd")
    {
        this->doUpdateVKListMenu(mVKList);
        this->addSeparator();
    }
    if (currentIM =="/Fcitx/im/mozc")
    {
        this->doUpdateMozcHiraganaListMenu(mMozcHiraganaList);
        this->doUpdateMozcToolListMenu(mMozcToolList);
        this->addSeparator();
    }
    else
    {
        foreach(const KimpanelProperty &prop, this->mStatusMenuList) {
              MyAction *menu=NULL;
              if(prop.icon.contains(PREFIX "/share/fcitx"))
                    menu = new MyAction(QIcon(prop.icon), prop.label, this);
              else
                    menu = new MyAction(QIcon::fromTheme(prop.icon), prop.label, this);
                menu->setMyActionType(StatusAction);
                menu->setProp(prop);
                this->addAction(menu);
        }
        this->addSeparator();
}
    this->addAction(QIcon::fromTheme("preferences-desktop"), gettext("ConfigureFcitx"));
    this->addAction(QIcon::fromTheme("preferences-desktop"), gettext("ConfigureIMPanel"));
    this->addSeparator();

    if (isUnity()) {
        this->addAction(gettext("Character Map"));
        this->addAction(gettext("Keyboard Layout Chart"));
        this->addAction(gettext("Text Entry Settings..."));
        this->addSeparator();
    }
        doUpdateSkinListMenu();
}

void SystemTrayMenu::triggerUpdateVKListMenu()
{
    mAgent->triggerProperty(QString("/Fcitx/vk"));
}

void SystemTrayMenu::triggerUpdateIMListMenu()
{
    mAgent->triggerProperty(QString("/Fcitx/im"));
}

void SystemTrayMenu::truggerUpdateMozcHiraganaMenu()
{
    mAgent->triggerProperty(QString("/Fcitx/mozc-composition-mode"));
}

void SystemTrayMenu::truggerUpdateMozcToolMenu()
{
    mAgent->triggerProperty(QString("/Fcitx/mozc-tool"));
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
    this->addMenu(mVKListMenu);
}

QString SystemTrayMenu::doUpdateIMListMenu(const QList<KimpanelProperty> &prop_list)
{
    bool checked = false;
    QString value = "fcitx-kbd";
    MyAction *firstAction = NULL, *action = NULL, *actionChecked = NULL;
    QList<KimpanelProperty>::const_iterator iter;

    for (iter = prop_list.begin(); iter != prop_list.end(); ++ iter) {
        if(iter->icon=="fcitx-kbd" || iter->icon==""||iter->icon.indexOf("indicator-keyboard")!=-1)
            action = new MyAction(QIcon::fromTheme("fcitx-kbd"), iter->label, this);
        else if(iter->icon.contains(PREFIX "/share/fcitx"))
            action = new MyAction(QIcon(iter->icon), iter->label, this);
        else
            action = new MyAction(QIcon::fromTheme(iter->icon), iter->label, this);
        action->setProp(*iter);
        action->setMyActionType(IMAction);
        this->addAction(action);
        if (firstAction == NULL)
            firstAction = action;
        action->setCheckable(true);
        if (iter->label == this->mCurtIMLabel) {
            if(iter->icon=="fcitx-kbd" || iter->icon==""||iter->icon.indexOf("indicator-keyboard")!=-1)
                 value = "fcitx-kbd";
            else
                 value = iter->key;
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
             value = "fcitx-kbd";
     return value;
}

void SystemTrayMenu::doUpdateMozcToolListMenu(const QList<KimpanelProperty> &prop_list)
{
    MyAction *menu;
    QList<KimpanelProperty>::const_iterator iter;
    mMozcHiraganaMenu->clear();
    for (iter = prop_list.begin(); iter != prop_list.end(); ++ iter) {
        menu = new MyAction(QIcon(iter->icon), iter->label, this);
        menu->setProp(*iter);
        mMozcHiraganaMenu->addAction(menu);
    }
    this->addMenu(mMozcHiraganaMenu);
}
void SystemTrayMenu::doUpdateMozcHiraganaListMenu(const QList<KimpanelProperty> &prop_list)
{
    MyAction *menu;
    QList<KimpanelProperty>::const_iterator iter;
    mMozcToolMenu->clear();
    for (iter = prop_list.begin(); iter != prop_list.end(); ++ iter) {
        menu =new MyAction(QIcon(iter->icon), iter->label, this);
        menu->setProp(*iter);
        mMozcToolMenu->addAction(menu);
    }
    this->addMenu(mMozcToolMenu);
}

bool SystemTrayMenu::isIMList(const QString &key)
{
    return key.startsWith("/Fcitx/im");
}

bool SystemTrayMenu::isVKList(const QString &key)
{
    return key.startsWith("/Fcitx/vk");
}

bool SystemTrayMenu::isMozcHiraganaList(const QString &key)
{
    return key.startsWith("/Fcitx/mozc-composition-mode");
}

bool SystemTrayMenu::isMozcToolList(const QString &key)
{
    return key.startsWith("/Fcitx/mozc-tool");
}

void SystemTrayMenu::execMenu(const QList<KimpanelProperty> &prop_list)
{
    QList<KimpanelProperty>::const_iterator iter = prop_list.begin();
    if (isIMList(iter->key))
        mIMList = prop_list;
    else if (isVKList(iter->key))
        mVKList = prop_list;
    else if (isMozcHiraganaList(iter->key))
        mMozcHiraganaList=prop_list;
    else if (isMozcToolList(iter->key))
        mMozcToolList = prop_list;
    else{
        for (iter = prop_list.begin(); iter != prop_list.end(); ++ iter) {
//            qDebug() << QString("execMenuCallback(1:%1 2:%2 3:%3 4:%4 5:%5 6:%6)").arg(iter->key)
//                .arg(iter->label).arg(iter->icon).arg(iter->tip).arg(iter->state).arg(iter->menu);
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
       // getRunCmdOuput("fcitx-qimpanel-configtool");
        if(configtoolPro->state()!=QProcess::Running)
                configtoolPro->start("fcitx-qimpanel-configtool");
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
        if (SkinAction == myAction->getMyActionType()) {
            skinMenuItemOnClick(myAction);
        } else if (myAction->getProp().key != "") {
//            qDebug()<<"---------------------"<<myAction->getProp().key;
            mAgent->triggerProperty(myAction->getProp().key);
        }
    }
        this->clear();
}

bool SystemTrayMenu::isUnity()
{
    const char *desktop = getenv("XDG_CURRENT_DESKTOP");
    return desktop && !strcmp(desktop, "Unity");
}

void SystemTrayMenu::doUpdateSkinListMenu()
{
    int i;
    size_t len;
    QDir skinDir;
    bool checked = false;
    MyAction *firstMenu = NULL, *menu;
    QFileInfoList list;
    QFileInfoList::Iterator iter;
    QString skinName = MainController::self()->getSkinName();
    SkinClass skinClass;
    bool localExist;
    MyAction *skinNameMenu = NULL;
    mSkinMenu->clear();
    QString localSkinPath = qgetenv("HOME") + "/.config/fcitx-qimpanel/skin/";

    for (i = 0; i < 1; i ++) {
        skinDir = QDir(localSkinPath);
        if (!skinDir.exists())
            continue;

        skinDir.setFilter(QDir::Dirs);
        list = skinDir.entryInfoList();
        for (iter = list.begin(); iter != list.end(); ++ iter) {
            if (iter->isDir() && "." != iter->fileName() && ".." != iter->fileName()) {
                QFile fcitxSkinConfFile(iter->absoluteFilePath() + "/fcitx_skin.conf");
                QFile sogouSkinConfFile(iter->absoluteFilePath() + "/skin.ini");

                if (fcitxSkinConfFile.exists()){
                    skinClass = FCITX;
                }else continue;

                menu = new MyAction(iter->fileName(), this);
                menu->setMyActionType(SkinAction);
                menu->setSkinPath(iter->absoluteFilePath() + "/");
                menu->setSkinClass(skinClass);
                mSkinMenu->addAction(menu);
                if (firstMenu == NULL)
                    firstMenu = menu;
                menu->setCheckable(true);
                if (iter->fileName() == skinName) {
                    checked = true;
                    menu->setChecked(true);
                    skinNameMenu = menu;
                }
            }
        }
    }

    char* ukSkinPath = getQimpanelSharePath("skin");

    for (i = 0; i < 1; i ++) {
        skinDir = QDir(ukSkinPath);
        if (!skinDir.exists())
            continue;

        skinDir.setFilter(QDir::Dirs);
        list = skinDir.entryInfoList();
        for (iter = list.begin(); iter != list.end(); ++ iter) {
            if (iter->isDir() && "." != iter->fileName() && ".." != iter->fileName()) {
                QFile fcitxSkinConfFile(iter->absoluteFilePath() + "/fcitx_skin.conf");
                QFile sogouSkinConfFile(iter->absoluteFilePath() + "/skin.ini");

                if (fcitxSkinConfFile.exists()){
                    skinClass = FCITX;
                }else continue;

                //check if exist in local
                localExist = false;
                QList<QAction *> localExistList = this->actions();
                QList<QAction *>::iterator localExistIter;
                for (localExistIter = localExistList.begin();
                    localExistIter != localExistList.end(); ++ localExistIter)
                {
                    if (((MyAction *)(*localExistIter))->text() == iter->fileName()) {
                        localExist = true;
                        break;
                    }
                }
                if (localExist)
                    continue;

                menu = new MyAction(iter->fileName(), this);
                menu->setMyActionType(SkinAction);
                //qDebug() << iter->absoluteFilePath();
                menu->setSkinPath(iter->absoluteFilePath() + "/");
                menu->setSkinClass(skinClass);
                mSkinMenu->addAction(menu);
                if (firstMenu == NULL)
                    firstMenu = menu;
                menu->setCheckable(true);
                if (iter->fileName() == skinName) {
                    checked = true;
                    menu->setChecked(true);
                    skinNameMenu = menu;
                }
            }
        }
    }

    char **skinPath = FcitxXDGGetPathWithPrefix(&len, "skin");
    for (i = 0; i < len; i ++) {
        skinDir = QDir(skinPath[i]);
        if (!skinDir.exists())
            continue;

        skinDir.setFilter(QDir::Dirs);
        list = skinDir.entryInfoList();
        for (iter = list.begin(); iter != list.end(); ++ iter) {
            if (iter->isDir() && "." != iter->fileName() && ".." != iter->fileName()) {
                QFile fcitxSkinConfFile(iter->absoluteFilePath() + "/fcitx_skin.conf");
                QFile sogouSkinConfFile(iter->absoluteFilePath() + "/skin.ini");

                if (fcitxSkinConfFile.exists()){
                    skinClass = FCITX;
                }else continue;

                menu = new MyAction(iter->fileName(), this);
                menu->setMyActionType(SkinAction);
                menu->setSkinPath(iter->absoluteFilePath() + "/");
                menu->setSkinClass(skinClass);
                mSkinMenu->addAction(menu);
                if (firstMenu == NULL)
                    firstMenu = menu;
                menu->setCheckable(true);
                if (iter->fileName() == skinName) {
                    checked = true;
                    menu->setChecked(true);
                    skinNameMenu = menu;
                }
            }
        }
    }

    if (!checked)
        firstMenu->setChecked(true);

    if (skinNameMenu == NULL)
        skinNameMenu = firstMenu;

    FcitxXDGFreePath(skinPath);

    skinMenuItemOnClick(skinNameMenu);
    this->addMenu(mSkinMenu);
}

void SystemTrayMenu::skinMenuItemOnClick(QAction* action)
{
    SkinBase *skin;
    MyAction *myAction = (MyAction *)action;
    MainController::self()->setSkinName(myAction->text());

    if (FCITX == myAction->getSkinClass())
        skin = new SkinFcitx;
    else qDebug() << "Load skin failed!";

    skin->loadSkin(myAction->getSkinPath());
    MainController::self()->setSkinBase(skin, myAction->getSkinClass());
}


