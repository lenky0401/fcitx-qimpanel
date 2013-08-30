
#ifndef __SYSTEM_TRAY_MENU_H__
#define __SYSTEM_TRAY_MENU_H__

#include <QMenu>
#include <QIcon>
#include "kimpanelagent.h"

enum ExecMenuType
{
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
    void setCurtIMLabel(QString label);

private slots:
    void triggerUpdateMainMenu();
    void triggerUpdateIMListMenu();
    void menuItemOnClick(QAction* action);

private:
    PanelAgent *mAgent;
public slots:
    void execMenu(const QList<KimpanelProperty> &prop_list);
private:
    void doUpdateIMListMenu(const QList<KimpanelProperty> &prop_list);

private:
    QString curtIMLabel;
    QMenu *mIMListMenu;
    //皮肤由前端自己组织
    //QMenu *mSkinMenu;
    ExecMenuType execMenuType;
};

#endif // __SYSTEM_TRAY_MENU_H__
