#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "fcitx-utils/utils.h"
#include "system_tray_menu.h"

SystemTrayMenu::SystemTrayMenu(QObject *parent)
    : QMenu()
{
    m_parent = parent;
    m_connection = new FcitxQtConnection(this);
    m_connection->setAutoReconnect(true);
    m_connection->startConnection();

    connect(m_connection, SIGNAL(connected()), SLOT(connected()));
}

SystemTrayMenu::~SystemTrayMenu()
{
    m_connection->endConnection();
    delete m_connection;
    if (m_improxy)
        delete m_improxy;
}

void SystemTrayMenu::init()
{
    QIcon::setThemeName("Humanity");
    this->addAction(QIcon::fromTheme("help-contents"),
        tr("Online &Help!"), this, SLOT(clickOnlineHelp()));
    
    this->addSeparator();

    this->addAction(QIcon::fromTheme("preferences-desktop"),
        tr("Configure"), this, SLOT(clickConfigure()));

    this->addAction(QIcon::fromTheme("view-refresh"),
        tr("Restart"), this, SLOT(clickRestart()));

    this->addAction(QIcon::fromTheme("application-exit"),
        tr("Exit"), m_parent, SLOT(quit()));
}

bool SystemTrayMenu::connected()
{
    if (!m_connection->isConnected())
        return false;
    
    if (m_improxy) {
        delete m_improxy;
        m_improxy = 0;
    }

    m_improxy = new FcitxQtInputMethodProxy(m_connection->serviceName(),
        QLatin1String(FCITX_IM_DBUS_PATH), *m_connection->connection(), this);
    
    if (m_improxy == NULL || !m_improxy->isValid())
        return false;
    
    return true;
}   
/*
void SystemTrayMenu::cleanUp()
{

    for(QHash<WId, FcitxQtICData *>::const_iterator i = m_icMap.constBegin(),
                                             e = m_icMap.constEnd(); i != e; ++i) {
        FcitxQtICData* data = i.value();

        if (data->proxy)
            delete data->proxy;
    }

    m_icMap.clear();

    if (m_improxy) {
        delete m_improxy;
        m_improxy = 0;
    }

    reset();
}*/

QStringList SystemTrayMenu::get_im_list()
{
    QString tmp;
    QStringList ret_value;
    FcitxQtInputMethodItemList im_item_list;
    FcitxQtInputMethodItemList::iterator im_iter;

    if (!is_connected_ok())
        return ret_value;

    im_item_list = m_improxy->iMList();

    for (im_iter = im_item_list.begin(); im_iter != im_item_list.end(); ++ im_iter) {
        tmp = im_iter->name() + m_separator +  im_iter->uniqueName() + m_separator
            +  im_iter->langCode();
        if (im_iter->enabled())
            tmp += m_separator + "true";
        else
            tmp += m_separator + "false";

        ret_value << tmp;
qDebug() << tmp;
    }

    //Debug
    //this->set_im_list(ret_value);

    m_im_list = ret_value;

    return ret_value;

    /*
    QString tmp;
    QStringList ret_value;
    FcitxQtInputMethodItemList im_item_list;
    FcitxQtInputMethodItemList::iterator im_iter;

    if (((m_improxy == NULL || !m_improxy->isValid()) && !connected()))
       return ret_value;

    im_item_list = m_improxy->iMList();
    //Debug
    //this->set_im_list(ret_value);
    for (im_iter = im_item_list.begin(); im_iter != im_item_list.end(); ++ im_iter) {
        qDebug() << im_iter->name(); 
        qDebug() << m_separator;
        qDebug() << im_iter->uniqueName(); 
        qDebug() <<  im_iter->langCode();
    }

    return ret_value;
*/
}

bool SystemTrayMenu::is_connected_ok()
{
    return !((m_improxy == NULL || !m_improxy->isValid()) && !connected());
}

void SystemTrayMenu::clickOnlineHelp()
{
//    QDesktopServices::openUrl(QUrl("http://fcitx-im.org/"));
    this->get_im_list();
}

void SystemTrayMenu::clickConfigure()
{
    fcitx_utils_launch_configure_tool();
}

void SystemTrayMenu::clickRestart()
{
    fcitx_utils_launch_tool("fcitx-qimpanel", "-r");
    fcitx_utils_launch_restart();
}


