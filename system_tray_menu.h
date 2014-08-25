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

#ifndef __SYSTEM_TRAY_MENU_H__
#define __SYSTEM_TRAY_MENU_H__

#include <QMenu>
#include <QIcon>
#include "kimpanelagent.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "config.h"
#include "skin/skinmenu.h"

enum ExecMenuType
{
    nullExecMenuType,
    updateVKListMenu,
    updateIMListMenu,
    //updateThemerMenu,
};

class SystemTrayMenu : public QMenu
{
    Q_OBJECT

public:
    SystemTrayMenu(PanelAgent *agent);
    virtual ~SystemTrayMenu();
    void init();

private slots:
    void triggerUpdateMainMenu();
    void triggerUpdateVKListMenu();
    void triggerUpdateIMListMenu();
#ifndef DISABLE_UK_SYNC	
    void triggerUpdateSyncMenu();
#endif
    void menuItemOnClick(QAction* action);

private:
    PanelAgent *mAgent;
public slots:
    void execMenu(const QList<KimpanelProperty> &prop_list);
    void registerProperties(const QList<KimpanelProperty> &props);
    void updateProperty(const KimpanelProperty &prop);

private:
    void doUpdateVKListMenu(const QList<KimpanelProperty> &prop_list);
    void doUpdateIMListMenu(const QList<KimpanelProperty> &prop_list);
    void appendIMListToMenu(QMenu *menu, const QList<KimpanelProperty> &prop_list);
    void startChildApp(const char *app_exe, const char * const argv[] = NULL);
#ifndef DISABLE_UK_SYNC
    void syncConfigUp();
    void syncConfigDown();
#endif	
public:
    void restart();

private:
    static bool isUnity();

private:
    QString mCurtIMLabel;
    //前两个用不到，见后端KimpanelRegisterAllStatus()函数
#define StatusMenuSkip (2)
    QList<KimpanelProperty> mIMList;
    QList<KimpanelProperty> mStatusMenuList;
    SkinMenu *mSkinMenu;
    QMenu *mVKListMenu;
    QMenu *mIMListMenu;
#ifndef DISABLE_UK_SYNC
    QMenu *mSyncMenu;
#endif
    ExecMenuType mExecMenuType;
};

#endif // __SYSTEM_TRAY_MENU_H__
