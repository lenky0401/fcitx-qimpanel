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
#include <QDir>

#include <fcitx-config/fcitx-config.h>

#include "skinmenu.h"
#include "../main_controller.h"
#include "../my_action.h"
#include "skinfcitx.h"
#include "skinsogou.h"
#include "../main.h"

SkinMenu::SkinMenu(const QString &title, QWidget *parent)
    : QMenu(title, parent)
{
    mSkinTypeMenu = NULL;
    triggerUpdateSkinListMenu();

    if (mSkinTypeMenu)
        menuItemOnClick(mSkinTypeMenu);

    QObject::connect(this, SIGNAL(aboutToShow()), this,
        SLOT(triggerUpdateSkinListMenu()));

    QObject::connect(this, SIGNAL(triggered(QAction*)), this,
        SLOT(menuItemOnClick(QAction *)));
}

SkinMenu::~SkinMenu()
{

}

void SkinMenu::triggerUpdateSkinListMenu()
{
    int i;
    size_t len;
    QDir skinDir;
    bool checked = false;
    MyAction *firstMenu = NULL, *menu;
    QFileInfoList list;
    QFileInfoList::Iterator iter;
    QString skinType = MainController::self()->getSkinType();

    mSkinTypeMap.clear();
    this->clear();

    char* ukSkinPath = getQimpanelSharePath("uk-default-skin");
    for (i = 0; i < 1; i ++) {
        skinDir = QDir(ukSkinPath);
        if (!skinDir.exists())
            continue;

        skinDir.setFilter(QDir::Dirs);
        list = skinDir.entryInfoList();
        for (iter = list.begin(); iter != list.end(); ++ iter) {
            if (iter->isDir() && "." != iter->fileName() && ".." != iter->fileName()) {
                QFile fcitxSkinConfFile(iter->absoluteFilePath() + "/fcitx_skin.conf");
                if (!fcitxSkinConfFile.exists())
                    continue;
                menu = new MyAction(iter->fileName(), this);
                //qDebug() << iter->absoluteFilePath();
                menu->setSkinPath(iter->absoluteFilePath() + "/");
                this->addAction(menu);
                if (firstMenu == NULL)
                    firstMenu = menu;
                menu->setCheckable(true);
                if (iter->fileName() == skinType) {
                    checked = true;
                    menu->setChecked(true);
                    mSkinTypeMenu = menu;
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
                    mSkinTypeMap.insert(iter->fileName(), FCITX);
                }else if (sogouSkinConfFile.exists()){
                    mSkinTypeMap.insert(iter->fileName(), SOGOU);
                }else continue;

                menu = new MyAction(iter->fileName(), this);
                menu->setSkinPath(iter->absoluteFilePath() + "/");
                this->addAction(menu);
                if (firstMenu == NULL)
                    firstMenu = menu;
                menu->setCheckable(true);
                if (iter->fileName() == skinType) {
                    checked = true;
                    menu->setChecked(true);
                    mSkinTypeMenu = menu;
                }
            }
        }
    }
    if (!checked)
        firstMenu->setChecked(true);

    if (mSkinTypeMenu == NULL)
        mSkinTypeMenu = firstMenu;

    FcitxXDGFreePath(skinPath);
}

void SkinMenu::menuItemOnClick(QAction *action)
{
    SkinBase *skin;
    MyAction *myAction = (MyAction *)action;
    MainController::self()->setSkinType(myAction->text());

    QMap<QString,int>::iterator it;
    it = mSkinTypeMap.find(myAction->text());
    if (FCITX == it.value())
        skin = new SkinFcitx;
    else if (SOGOU == it.value())
        skin = new SkinSogou;
    else qDebug() << "Load skin failed!";

    skin->loadSkin(myAction->getSkinPath());
    MainController::self()->setSkinBase(skin);
}
