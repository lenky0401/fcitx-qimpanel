#include <QDebug>
#include <stdio.h>
#include <QApplication>
#include <QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include "main_model.h"
#include "candidate_word.h"
#include "main_controller.h"
#include "kimpanelagent.h"
#include "toplevel.h"

MainController::MainController(int &argc, char **argv)
    : QApplication(argc, argv), mTopLevel(0), mModel(0), mAgent(0), mView(0)
{

}

MainController::~MainController()
{
    if (mModel)
        delete mModel;

    if (mAgent)
        delete mAgent;

    if (mView)
        delete mView;

    if (mTopLevel)
        delete mTopLevel;
}

bool MainController::init()
{
    MainController::setApplicationName("fcitx-qimpanel");

    qmlRegisterType<CandidateWord>();

    if ((mTopLevel = new (std::nothrow)TopLevel) == NULL)
        return false;

    if ((mView = new (std::nothrow)QDeclarativeView) == NULL)
        return false;

    if ((mModel = new (std::nothrow)MainModel) == NULL)
        return false;

    if ((mTimer = new (std::nothrow)QTimer(this)) == NULL)
        return false;

    if ((mAgent = new (std::nothrow)PanelAgent(this)) == NULL)
        return false;

    mAgent->created();

    if ((systemTray = new (std::nothrow)QSystemTrayIcon(
        QIcon::fromTheme("fcitx-kbd"), this)) == NULL)
    {
        return false;
    }
    if ((trayMenu = new (std::nothrow)SystemTrayMenu()) == NULL)
        return false;

    trayMenu->init();

    systemTray->setContextMenu(trayMenu);
    systemTray->setToolTip("fcitx-qimpanel");
    systemTray->show();

    mTopLevel->setCenterWidget(mView);

    mView->setContentsMargins(0, 0, 0, 0);
    mView->setResizeMode(QDeclarativeView::SizeViewToRootObject);
    mView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    mView->viewport()->setAutoFillBackground(false);
    mView->rootContext()->setContextProperty("mainCtrl", this);
    mView->rootContext()->setContextProperty("mainModel", mModel);
    this->mUrl = QUrl("qrc:/qml/vertical.qml");
    mView->setSource(this->mUrl);
    //mView->setAttribute(Qt::WA_X11NetWmWindowTypeToolTip, true);

    //直接使用hide()会出现元素错位的情况，应该是qt/qml的内部bug
    //这里采用将窗体大小设置为(0, 0)的方式实现hide()的等同效果
    //mView->setWindowTitle("fcitx-qimpanel");
    //mView->setAutoFillBackground(true);
    //mView->setWindowOpacity(10);

    //QObject::connect(mView->engine(), SIGNAL(quit()), qApp, SLOT(quit()));
    QObject::connect(mTimer, SIGNAL(timeout()), this, SLOT(hideTips()));

    QObject::connect(mAgent,
        SIGNAL(updateProperty(KimpanelProperty)), this,
        SLOT(updateProperty(KimpanelProperty)));

    QObject::connect(mAgent,
        SIGNAL(registerProperties(const QList<KimpanelProperty>)), this,
        SLOT(registerProperties(const QList<KimpanelProperty>)));

    QObject::connect(mAgent,
        SIGNAL(updatePreeditText(QString, QList<TextAttribute>)),
        this, SLOT(updatePreeditText(QString, QList<TextAttribute>)));

    QObject::connect(mAgent,
        SIGNAL(updateLookupTable(KimpanelLookupTable)),
        this, SLOT(updateLookupTable(KimpanelLookupTable)));

    QObject::connect(mAgent,
        SIGNAL(updateLookupTableFull(KimpanelLookupTable, int, int)),
        this, SLOT(updateLookupTableFull(KimpanelLookupTable, int, int)));

    QObject::connect(mAgent,
        SIGNAL(updateSpotLocation(int, int)),
        this, SLOT(updateSpotLocation(int, int)));

    QObject::connect(mAgent,
        SIGNAL(updateSpotRect(int, int, int, int)),
        this, SLOT(updateSpotRect(int, int, int, int)));

    QObject::connect(mAgent,
        SIGNAL(showPreedit(bool)),
        this, SLOT(showPreedit(bool)));

    QObject::connect(mAgent,
        SIGNAL(showAux(bool)),
        this, SLOT(showAux(bool)));

    QObject::connect(mAgent,
        SIGNAL(updateAux(QString, QList<TextAttribute>)),
        this, SLOT(updateAux(QString, QList<TextAttribute>)));

    QObject::connect(mAgent,
        SIGNAL(showLookupTable(bool)),
        this, SLOT(showLookupTable(bool)));

    QObject::connect(mAgent,
        SIGNAL(updateLookupTableCursor(int)),
        this, SLOT(updateLookupTableCursor(int)));

    QObject::connect(mAgent,
        SIGNAL(updatePreeditCaret(int)),
        this, SLOT(updatePreeditCaret(int)));

	return true;
}

void MainController::hideTips()
{
    this->mTimer->stop();
    mModel->setTipsString("");
    mTopLevel->setVisible(false);
    printf("hideTips()\n");
    mView->setSource(this->mUrl);
}

void MainController::showTips(const QString tipsString)
{
    if (QUrl("qrc:/qml/tips.qml") != mView->source())
        mView->setSource(QUrl("qrc:/qml/tips.qml"));

    mModel->setTipsString(tipsString);
    mTopLevel->setVisible(true);
    if (this->mTimer->isActive())
        this->mTimer->stop();
    this->mTimer->start(1000);
}

void MainController::updateProperty(const KimpanelProperty &prop)
{
    QIcon icon = QIcon::fromTheme(prop.icon, QIcon::fromTheme("fcitx-kbd"));
    systemTray->setIcon(icon);
    //systemTray->showMessage(prop.label, prop.tip, QSystemTrayIcon::Information, 100);
    //qDebug() << QString("updateProperty(1:%1 2:%2 3:%3 4:%4 5:%5)").arg(prop.key)
    //        .arg(prop.label).arg(prop.icon).arg(prop.tip).arg(prop.state);
    mModel->resetData();
}

void MainController::registerProperties(const QList<KimpanelProperty> &props)
{
    QList<KimpanelProperty>::const_iterator iter;

    //for (iter = props.begin(); iter != props.end(); ++ iter) {
    //    qDebug() << QString("updateProperty(1:%1 2:%2 3:%3 4:%4 5:%5)").arg(iter->key)
    //            .arg(iter->label).arg(iter->icon).arg(iter->tip).arg(iter->state);
    //}
}

void MainController::updatePreeditText(const QString inputString,
    QList<TextAttribute> attributes)
{
    mModel->setInputString(inputString);
}

void MainController::updateLookupTable(const KimpanelLookupTable &lookup_table)
{
    mModel->setCandidateWords(lookup_table);
}

void MainController::updateLookupTableFull(const KimpanelLookupTable &lookup_table,
    int cursor, int layout)
{
    mModel->setHighLight(cursor);
    updateLookupTable(lookup_table);
}

void MainController::updateSpotLocation(int x, int y)
{
    //printf("%d %d\n", x, y);
}

void MainController::updateSpotRect(int x, int y, int w, int h)
{
    mTopLevel->setSpotRect(QRect(QPoint(x, y), QSize(w, h)));
    //printf("w:%d, h:%d\n", w, h);
}

void MainController::showPreedit(bool to_show)
{
    printf("showPreedit: %d\n", to_show);
}

void MainController::showAux(bool to_show)
{
    printf("showAux: %d\n", to_show);
}

void MainController::updateAux(const QString &text, const QList<TextAttribute> &attr)
{
    if (text == "")
        return;
    this->showTips(text);
    qDebug() << QString("updateAux(%1)").arg(text);
}

void MainController::showLookupTable(bool to_show)
{
    printf("showLookupTable: %d\n", to_show);
    if (this->mTimer->isActive()) {
        if (to_show == false)
            return;
        else
            hideTips();
    }

    mTopLevel->setVisible(to_show);
}

void MainController::updateLookupTableCursor(int pos)
{
    //printf("pos: %d\n", pos);
}

void MainController::getPrevPage()
{
    mAgent->lookupTablePageUp();
}

void MainController::getNextPage()
{
    mAgent->lookupTablePageDown();
}

void MainController::selectCandidate(int index)
{
    mAgent->selectCandidate(index);
}

void MainController::updatePreeditCaret(int pos)
{
    mModel->setInputStringCursorPos(pos);
}
