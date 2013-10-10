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

#ifndef __SKIN_MENU_H__
#define __SKIN_MENU_H__

#include <QMenu>
#include <QIcon>
#include "../my_action.h"

#define FCITX 1
#define SOGOU 2

class SkinMenu : public QMenu
{
    Q_OBJECT

public:
    SkinMenu(const QString &title, QWidget *parent);
    virtual ~SkinMenu();

private slots:
    void triggerUpdateSkinListMenu();
    void menuItemOnClick(QAction* action);

private:
    MyAction *mSkinTypeMenu;
    QMap<QString,int> mSkinTypeMap;
};

#endif // __SKIN_MENU_H__
