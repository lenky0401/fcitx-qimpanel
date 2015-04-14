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
#include <QProcess>
#include "config.h"
class SystemTrayMenu : public QMenu
{
    Q_OBJECT

public:
    SystemTrayMenu(PanelAgent *agent);
    virtual ~SystemTrayMenu();
    void init();

private:
    void updateMainMenu();

private slots:
    void clearMenu();
    void triggerUpdateVKListMenu();
    void triggerUpdateIMListMenu();
    void truggerUpdateMozcHiraganaMenu();
    void truggerUpdateMozcToolMenu();
    void menuItemOnClick(QAction* action);

private:
    PanelAgent *mAgent;
public slots:
    void execMenu(const QList<KimpanelProperty> &prop_list);
    void registerProperties(const QList<KimpanelProperty> &props);
    void updateProperty(const KimpanelProperty &prop);

private:
    //return True if is the fcitx-kbd checked.
    QString doUpdateIMListMenu(const QList<KimpanelProperty> &prop_list);
    void doUpdateVKListMenu(const QList<KimpanelProperty> &prop_list);

    void doUpdateMozcHiraganaListMenu(const QList<KimpanelProperty> &prop_list);
    void doUpdateMozcToolListMenu(const QList<KimpanelProperty> &prop_list);
    void startChildApp(const char *app_exe, const char * const argv[] = NULL);
public:
    void restart();

private:
    static bool isUnity();
    static bool isIMList(const QString &key);
    static bool isVKList(const QString &key);
    static bool isMozcHiraganaList(const QString &key);
    static bool isMozcToolList(const QString &key);
private:
    QString mCurtIMLabel;
    //前两个用不到，见后端KimpanelRegisterAllStatus()函数
#define StatusMenuSkip (2)
    QList<KimpanelProperty> mIMList;
    QList<KimpanelProperty> mVKList;
    QList<KimpanelProperty> mMozcToolList;
    QList<KimpanelProperty> mMozcHiraganaList;
    QList<KimpanelProperty> mStatusMenuList;
    QProcess *configtoolPro ;
#ifdef IS_QT_4
    QMenu *mSkinMenu;
    QMenu *mVKListMenu;
    QMenu *mMozcToolMenu;
    QMenu *mMozcHiraganaMenu;
#endif
private:
    void skinMenuItemOnClick(QAction* action);
    void doUpdateSkinListMenu();
};

#endif // __SYSTEM_TRAY_MENU_H__
