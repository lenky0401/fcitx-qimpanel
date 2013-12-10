/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  lenky gao    lenky0401@gmail.com/gaoqunkai@ubuntukylin.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QDebug>
#include <QSettings>
#include <QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include "main_model.h"
#include "candidate_word.h"
#include "main_controller.h"
#include "kimpanelagent.h"
#include "toplevel.h"

MainController* MainController::mSelf = 0;

MainController* MainController::self()
{
    if (!mSelf) {
        mSelf = new MainController;
        mSelf->init();
    }
    return mSelf;
}

MainController::MainController()
{

}

void MainController::loadCfg()
{
    QSettings *settings = new QSettings("fcitx-qimpanel", "main");
    settings->beginGroup("base");
    mIsHorizontal = !settings->value("VerticalList", false).toBool();
    qDebug() << "mIsHorizontal:" << mIsHorizontal;
    mSkinName = settings->value("CurtSkinType", "ubuntukylin-dark1").toString();
    qDebug() << "mSkinName:" << mSkinName;
    settings->endGroup();
    delete settings;
}

void MainController::init()
{
    loadCfg();

    qmlRegisterType<CandidateWord>();

    mTopLevel = new TopLevel;
    mView = new QDeclarativeView;
    mModel = MainModel::self();
    mModel->setIsHorizontal(mIsHorizontal);

    mSkinBase = new SkinBase;

    mTopLevel->setCenterWidget(mView);

    mView->setContentsMargins(0, 0, 0, 0);
    mView->setResizeMode(QDeclarativeView::SizeViewToRootObject);
    mView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    mView->viewport()->setAutoFillBackground(false);
    mView->rootContext()->setContextProperty("mainCtrl", this);
    mView->rootContext()->setContextProperty("mainModel", mModel);
    mView->rootContext()->setContextProperty("mainSkin", mSkinBase);
    mView->rootContext()->setContextProperty("mainWidget", mTopLevel);
    mView->setSource(QUrl("qrc:/qml/main.qml"));

    mAgent = new PanelAgent(this);
    mSystemTray = new QSystemTrayIcon(QIcon::fromTheme("fcitx"), this);
    mTrayMenu = new SystemTrayMenu(mAgent);

    mAgent->created();
    mTrayMenu->init();

    mSystemTray->setContextMenu(mTrayMenu);
    mSystemTray->setToolTip("fcitx-qimpanel");
    mSystemTray->show();

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

SystemTrayMenu* MainController::getTrayMenu()
{
	return mTrayMenu;
}

void MainController::setSkinBase(SkinBase *skinBase, int skinType)
{
   if (mSkinBase != skinBase)
       delete mSkinBase;
   mSkinBase = skinBase;
   mView->rootContext()->setContextProperty("mainSkin", mSkinBase);

   switch (skinType) {
       case SOGOU:
           qDebug() << "SkinType is sogou";
           mView->setSource(QUrl("qrc:/qml/sogou.qml"));
           break;
       case FCITX:
       default:
           qDebug() << "SkinType is default";
           mView->setSource(QUrl("qrc:/qml/main.qml"));
   }
}

QString MainController::getSkinName()
{
    return mSkinName;
}

void MainController::setSkinName(QString skinName)
{
    mSkinName = skinName;
    QSettings *settings = new QSettings("fcitx-qimpanel", "main");
    settings->beginGroup("base");
    settings->setValue("CurtSkinType", skinName);
    settings->endGroup();
    delete settings;
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
    bool isHorizontal;

    switch (layout) {
    case CLH_Vertical:
        isHorizontal = false;
        break;
    case CLH_Horizontal:
        isHorizontal = true;
        break;
    default:
        isHorizontal = mIsHorizontal;
        break;
    }

    if (isHorizontal != mModel->isHorizontal()) {
        mModel->setIsHorizontal(isHorizontal);
        mSkinBase->reloadSkin();
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
    mTopLevel->setTopLevelVisible(mModel->showTips(), mModel->showPreedit(), mModel->showLookupTable());
}

void MainController::showAux(bool to_show)
{
    mModel->setShowTips(to_show);
    mTopLevel->setTopLevelVisible(mModel->showTips(), mModel->showPreedit(), mModel->showLookupTable());
}

void MainController::updateAux(const QString &text, const QList<TextAttribute> &attr)
{
    mModel->setTipsString(text);
}

void MainController::showLookupTable(bool to_show)
{
    mModel->setShowLookupTable(to_show);
    mTopLevel->setTopLevelVisible(mModel->showTips(), mModel->showPreedit(), mModel->showLookupTable());
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

