
#ifndef __SYSTEM_TRAY_MENU_H__
#define __SYSTEM_TRAY_MENU_H__

#include <QMenu>
#include <QIcon>
#include "kimpanelagent.h"

enum ExecMenuType
{
    nullExecMenuType,
    updateIMListMenu,
    //updateSkinMenu,
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
    void triggerUpdateIMListMenu();
    void menuItemOnClick(QAction* action);

private:
    PanelAgent *mAgent;
public slots:
    void execMenu(const QList<KimpanelProperty> &prop_list);
    void registerProperties(const QList<KimpanelProperty> &props);
    void updateProperty(const KimpanelProperty &prop);

private:
    void doUpdateIMListMenu(const QList<KimpanelProperty> &prop_list);
    bool dynamicMenuItemOnClick(QAction *action);

private:
    QString mCurtIMLabel;
    //前两个用不到，见后端KimpanelRegisterAllStatus()函数
#define StatusMenuSkip (2)
    QList<KimpanelProperty> mStatusMenuList;
    QList<KimpanelProperty> mIMListMenuList;
    QMenu *mIMListMenu;
    //皮肤由前端自己组织
    //QMenu *mSkinMenu;
    ExecMenuType mExecMenuType;
};

#endif // __SYSTEM_TRAY_MENU_H__
