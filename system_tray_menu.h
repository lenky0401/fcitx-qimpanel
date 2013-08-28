
#ifndef __SYSTEM_TRAY_MENU_H__
#define __SYSTEM_TRAY_MENU_H__

#include <QMenu>
#include <QIcon>
#include <fcitx-qt/fcitxqtconnection.h>
#include <fcitx-qt/fcitxqtinputmethodproxy.h>
#include <fcitx/module/ipc/ipc.h>

class SystemTrayMenu : public QMenu
{
    Q_OBJECT
public:
    QString m_separator;
public:
    SystemTrayMenu(QObject *parent);
    virtual ~SystemTrayMenu();
    void init();
//    void cleanUp();
    Q_INVOKABLE QStringList get_im_list();
    bool is_connected_ok();
private:
    QObject *m_parent;
    QStringList m_im_list;
    FcitxQtConnection *m_connection;
    FcitxQtInputMethodProxy *m_improxy;
private slots:
    void clickOnlineHelp();
    void clickConfigure();
    void clickRestart();
    bool connected();

};

#endif // __SYSTEM_TRAY_MENU_H__
