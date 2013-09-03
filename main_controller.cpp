#include <QDebug>
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
    mLayout = true;
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

    if (mSystemTray)
        delete mSystemTray;

    if (mTrayMenu)
        delete mTrayMenu;
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

    if ((mAgent = new (std::nothrow)PanelAgent(this)) == NULL)
        return false;

    mAgent->created();

    if ((mSystemTray = new (std::nothrow)QSystemTrayIcon(
        QIcon::fromTheme("fcitx"), this)) == NULL)
    {
        return false;
    }
    if ((mTrayMenu = new (std::nothrow)SystemTrayMenu(mAgent)) == NULL)
        return false;

    mTrayMenu->init();

    mSystemTray->setContextMenu(mTrayMenu);
    mSystemTray->setToolTip("fcitx-qimpanel");
    mSystemTray->show();

    mTopLevel->setCenterWidget(mView);

    mView->setContentsMargins(0, 0, 0, 0);
    mView->setResizeMode(QDeclarativeView::SizeViewToRootObject);
    mView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    mView->viewport()->setAutoFillBackground(false);
    mView->rootContext()->setContextProperty("mainCtrl", this);
    mView->rootContext()->setContextProperty("mainModel", mModel);
    mView->setSource(QUrl("qrc:/qml/main.qml"));
    //mView->setAttribute(Qt::WA_X11NetWmWindowTypeToolTip, true);

    //直接使用hide()会出现元素错位的情况，应该是qt/qml的内部bug
    //这里采用将窗体大小设置为(0, 0)的方式实现hide()的等同效果
    //mView->setWindowTitle("fcitx-qimpanel");
    //mView->setAutoFillBackground(true);
    //mView->setWindowOpacity(10);

    //QObject::connect(mView->engine(), SIGNAL(quit()), qApp, SLOT(quit()));

    mTopLevel->setVisible(true);

    QObject::connect(mAgent,
        SIGNAL(updateProperty(KimpanelProperty)), this,
        SLOT(updateProperty(KimpanelProperty)));

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

void MainController::updateProperty(const KimpanelProperty &prop)
{
    if (tr("No input window") == prop.label) {
        QIcon icon = QIcon::fromTheme("fcitx");
        mSystemTray->setIcon(icon);
        return;
    }
    QIcon icon = QIcon::fromTheme(prop.icon, QIcon::fromTheme("fcitx-kbd"));
    mSystemTray->setIcon(icon);
    mModel->resetData();
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
    switch (layout) {
    case CLH_Vertical:
        mModel->setIsHorizontal(false);
        break;
    case CLH_Horizontal:
        mModel->setIsHorizontal(true);
        break;
    default:
        mModel->setIsHorizontal(mLayout);
        break;
    }

    mModel->setHighLight(cursor);
    updateLookupTable(lookup_table);
}

void MainController::updateSpotLocation(int x, int y)
{

}

void MainController::updateSpotRect(int x, int y, int w, int h)
{
    mTopLevel->setSpotRect(QRect(QPoint(x, y), QSize(w, h)));
}

void MainController::showPreedit(bool to_show)
{
    mModel->setShowPreedit(to_show);
}

void MainController::showAux(bool to_show)
{
    mModel->setShowTips(to_show);
}

void MainController::updateAux(const QString &text, const QList<TextAttribute> &attr)
{
    mModel->setTipsString(text);
}

void MainController::showLookupTable(bool to_show)
{
    mModel->setShowLookupTable(to_show);
}

void MainController::updateLookupTableCursor(int pos)
{
//    qDebug() << QString("updateLookupTableCursor: %1").arg(pos);
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

