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
#include "main_controller.h"

MainApplication::MainApplication(int &argc, char **argv)
    : QApplication(argc, argv)
{

}

bool MainApplication::init()
{
    MainController *ctrl;
    QDeclarativeView *mView;
    
    MainApplication::setApplicationName("fcitx-kimpanel");

    if ((ctrl = new (std::nothrow)MainController) == NULL || !ctrl->init())
        return false;

    if ((mView = new (std::nothrow)QDeclarativeView) == NULL)
        return false;

    mView->rootContext()->setContextProperty("mainModel", ctrl->getModel());
    mView->setSource(QUrl::fromLocalFile("../main.qml"));
    
    mView->setStyleSheet("background:transparent;");
    mView->setAttribute(Qt::WA_TranslucentBackground);
    //mView->setWindowFlags(Qt::FramelessWindowHint);
    mView->setWindowTitle("fcitx-kimpanel");
    mView->setAutoFillBackground(false);
    mView->setWindowOpacity(10);

//    QDesktopWidget* desktop = QApplication::desktop();
//    QSize size = mView->sizeHint();
//    int width = desktop->width();
//    int height = desktop->height();
//    int mw = size.width();
//    int mh = size.height();
//    int centerW = (width/2) - (mw/2);
//    int centerH = (height/2) - (mh/2);
//    mView->move(centerW, centerH);

    QObject::connect(mView->engine(), SIGNAL(quit()), qApp, SLOT(quit()));
    mView->show();

    return true;
}

MainApplication::~MainApplication()
{

}

