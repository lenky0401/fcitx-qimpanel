#include <QDebug>
#include <stdio.h>
#include <QApplication>
#include <QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>

#include "main_model.h"
#include "candidate_word.h"
#include "main_controller.h"
#include "kimpanelagent.h"

MainController::MainController(int &argc, char **argv)
    : QApplication(argc, argv), mModel(0), mAgent(0), mView(0)
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
}

bool MainController::init()
{
    MainController::setApplicationName("fcitx-kimpanel");

    qmlRegisterType<CandidateWord>();

    if ((mView = new (std::nothrow)QDeclarativeView) == NULL)
        return false;

    if ((mModel = new (std::nothrow)MainModel) == NULL)
        return false;

    if ((mAgent = new (std::nothrow)PanelAgent(this)) == NULL)
        return false;

    mAgent->created();

    mView->rootContext()->setContextProperty("mainModel", mModel);
    mView->setSource(QUrl::fromLocalFile("../main.qml"));

    mView->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool |
        Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    mView->setAttribute(Qt::WA_TranslucentBackground, true);
    //mView->setWindowTitle("fcitx-kimpanel");
    //mView->setAutoFillBackground(true);
    //mView->setWindowOpacity(10);

    //QObject::connect(mView->engine(), SIGNAL(quit()), qApp, SLOT(quit()));

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
        SIGNAL(showLookupTable(bool)),
        this, SLOT(showLookupTable(bool)));

    QObject::connect(mAgent,
        SIGNAL(updateLookupTableCursor(int)),
        this, SLOT(updateLookupTableCursor(int)));

	return true;
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
    updateLookupTable(lookup_table);
}

void MainController::updateSpotLocation(int x, int y)
{
    //printf("%d %d\n", x, y);
}

void MainController::updateSpotRect(int x, int y, int w, int h)
{
    int yOffset = 10;
    mView->move(x, y + h + yOffset);
}

void MainController::showLookupTable(bool to_show)
{
    if (to_show)
        mView->show();
    else
        mView->hide();
}

void MainController::updateLookupTableCursor(int pos)
{
    //printf("pos: %d\n", pos);
}
