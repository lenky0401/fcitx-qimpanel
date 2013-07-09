#include <QDeclarativeView>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeItem>
#include <QMetaObject>
#include <QDeclarativeContext>
#include <QDesktopWidget>
#include "main_application.h"
#include "kimpanelagent.h"

MainApplication::MainApplication(int &argc, char **argv)
    : QApplication(argc, argv), m_view(0)
{

}

bool MainApplication::setup()
{
    QObject *rootObject;
    
    MainApplication::setApplicationName("fcitx-kimpanel");

    if ((m_view = new (std::nothrow)QDeclarativeView) == NULL)
        return false;
    m_view->rootContext()->setContextProperty("main_window_view", m_view);
    m_view->setSource(QUrl::fromLocalFile("../main.qml"));
    
    m_view->setStyleSheet("background:transparent;");
    m_view->setAttribute(Qt::WA_TranslucentBackground);
//    m_view->setWindowFlags(Qt::FramelessWindowHint);
    m_view->setWindowTitle("fcitx-kimpanel");
    m_view->setAutoFillBackground(false);
    m_view->setWindowOpacity(10);

    QDesktopWidget* desktop = QApplication::desktop();
    QSize size = m_view->sizeHint();
    int width = desktop->width();
    int height = desktop->height();
    int mw = size.width();
    int mh = size.height();
    int centerW = (width/2) - (mw/2);
    int centerH = (height/2) - (mh/2);
    m_view->move(centerW, centerH);

    QObject::connect(m_view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));
    m_view->rootContext()->setContextProperty("WindowControl", m_view);

    if ((m_agent = new (std::nothrow)PanelAgent(this)) == NULL)
        return false;

    if ((rootObject = dynamic_cast<QObject *>(m_view->rootObject())) == NULL)
        return false;

    QObject::connect(m_agent, 
        SIGNAL(updatePreeditText(QString, QList<TextAttribute>)),
        rootObject, SLOT(update_input_string(QVariant, QVariantList)));
//    QObject::connect(m_agent, SIGNAL(showPreedit(bool)), 
//        SLOT(setVisible(bool)));

    m_agent->created();
    m_view->show();

    return true;
}

MainApplication::~MainApplication()
{
    if (m_view) {
        delete m_view;
    }
    
    if (m_agent) {
        delete m_agent;
    }
}

