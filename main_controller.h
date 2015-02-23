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

#ifndef __MAIN_CONTROLLER_H__
#define __MAIN_CONTROLLER_H__

#include <QtQuickWidgets>
#include "main_model.h"
#include "system_tray_menu.h"
#include "kimpanelagent.h"
#include "toplevel.h"
#include "skin/skinbase.h"
#include "skin/skinmenu.h"

//必须与FcitxCandidateLayoutHint的定义一致
enum CandidateLayout {
    CLH_NotSet,
    CLH_Vertical,
    CLH_Horizontal
};

class MainController : public QObject
{
    Q_OBJECT
    // 定义Interface名称为"com.test.hotel"
    Q_CLASSINFO("D-Bus Interface", "com.fcitx_qimpanel.hotel")

public:
    static MainController* self();
    virtual ~MainController();
    void init();
    void loadCfg();

private:
    explicit MainController();
    static MainController *mSelf;

private:
    TopLevel *mTopLevel;
    MainModel *mModel;
    PanelAgent *mAgent;
    SkinBase *mSkinBase;
    QQuickWidget *mView;
    QUrl mUrl;
    QTimer *mTimer;
    QSystemTrayIcon *mSystemTray;
    SystemTrayMenu *mTrayMenu;
    bool mIsHorizontal;
    QString mSkinName;

private:
    QSocketNotifier *mSocketNotifier;
private slots:
//    void handleSig();

public:
    int mSigFd[2];

public:
    void setSkinBase(SkinBase *skinBase, int skinType);
    QString getSkinName();
    void setSkinName(QString skinName);
    SystemTrayMenu* getTrayMenu();
    void creatDBusService();

public slots:
    void updateProperty(const KimpanelProperty &prop);
    void updatePreeditText(const QString inputString, 
        QList<TextAttribute> attributes);

    void updateLookupTable(const KimpanelLookupTable &lookup_table);
    void updateLookupTableFull(const KimpanelLookupTable &lookup_table,
        int cursor, int layout);

    void updateSpotLocation(int x, int y);
    void updateSpotRect(int x, int y, int w, int h);
    void showPreedit(bool to_show);
    void showAux(bool to_show);
    void updateAux(const QString &text, const QList<TextAttribute> &attr);
    void showLookupTable(bool to_show);
    void updateLookupTableCursor(int pos);
    void updatePreeditCaret(int pos);
    void qtDbusSot_restartQimpanel();


public:
    Q_INVOKABLE void getPrevPage();
    Q_INVOKABLE void getNextPage();
    Q_INVOKABLE void selectCandidate(int index);
};

#endif // __MAIN_CONTROLLER_H__
