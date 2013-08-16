
#ifndef __SYSTEM_TRAY_MENU_H__
#define __SYSTEM_TRAY_MENU_H__

#include <QMenu>
#include <QIcon>

class SystemTrayMenu : public QMenu
{
    Q_OBJECT

public:
    SystemTrayMenu();
    virtual ~SystemTrayMenu();
    void init();

private slots:
    void clickOnlineHelp();
    void clickSystemRestart();

};

#endif // __SYSTEM_TRAY_MENU_H__
