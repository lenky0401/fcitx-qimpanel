#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QTime>
#include <libintl.h>

#define FCITXSKINSYSTEM_PATH (PREFIX "/share/fcitx-qimpanel/skin/")

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qmlRegisterType<CandidateWord>();//注册CandidateWord列表到qml
    #ifdef IS_QT_5
        qmlView = new QQuickWidget;
    #endif
    #ifdef IS_QT_4
         qmlView = new QDeclarativeView;
    #endif
    listWidgetChangeClearFlag = false;
    mSkinFcitx = new SkinFcitx;
    mMainModer = MainModel::self();
    mSettings = new QSettings("fcitx-qimpanel", "main");
    mSettings->setIniCodec("UTF-8");
    mLayout = new QHBoxLayout(ui->widgetSkinPreview);
    localPath = qgetenv("HOME") + "/.config/fcitx-qimpanel/skin/";
    this->setWindowTitle(gettext("Qimpanel Settings"));
    loadMainConf();
    ui->tabWidget->setCurrentIndex(0);
    ui->listWidgetAllSkin->setCurrentRow(0);
    mMainModer->resetData();
    changeMainWindowSize();   

    ui->tabWidget->setTabText(0,gettext("Appearance"));
    ui->tabWidget->setTabText(1,gettext("Skin Design"));
    ui->labelVerticalList->setText(gettext("Vertical List"));
    ui->labelSkinType->setText(gettext("Skin Type"));
    ui->radioButtonHorizontal->setText(gettext("Horizontal"));
    ui->radioButtonVertical->setText(gettext("Vertical"));

    ui->labelAllSkin->setText(gettext("All Skins"));
    ui->labelPreview->setText(gettext("Preview"));
    ui->labelDescription->setText(gettext("Description: Click to select and preview, double-click local to edit, save locally."));
    ui->pushButtonApply->setText(gettext("&Apply"));
    ui->pushButtonCancel->setText(gettext("&Cancel"));

    connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(sltOnPushButtonCancel()));
    connect(ui->pushButtonApply, SIGNAL(clicked()), this, SLOT(sltOnPushButtonApply()));

    connect(ui->tabWidget, SIGNAL(currentChanged(QWidget *)), this, SLOT(sltOnCurrentChanged(QWidget *)));

    connect(ui->listWidgetAllSkin, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(sltOnAllSkinItemDoubleClicked(QListWidgetItem*)));

    connect(ui->comboBoxSkinType,SIGNAL(currentIndexChanged(int)),this,SLOT(setListWidgetAllSkinIndex(int)));
    linkQtDbusServer();
}

MainWindow::~MainWindow()
{
    mSettings->sync();
    if(mSettings!=NULL)
        delete mSettings;
    delete ui;
}

void MainWindow::changeMainWindowSize()
{
    int y = 0;
    int x = 0;

    if (ui->radioButtonVertical->isChecked()) {
        y = 120;

        this->setFixedSize(560+x, 360 + y);
        ui->tabWidget->setFixedHeight(311 + y);
        ui->tabWidget->setFixedWidth(561 + x);
        ui->widgetSkinPreview->setFixedWidth(381 + x);
        ui->widgetSkinPreview->setFixedHeight(121 + y + 40);

        ui->pushButtonCancel->setGeometry(360+x, 320 + y, 81, 31);
        ui->pushButtonApply->setGeometry(450+x, 320 + y, 81, 31);


    } else {

        this->setFixedSize(560+x, 360 + y);
        ui->tabWidget->setFixedHeight(311 + y);
        ui->tabWidget->setFixedWidth(561 + x);
        ui->widgetSkinPreview->setFixedWidth(381 + x);
        ui->widgetSkinPreview->setFixedHeight(121 + y + 40);

        ui->pushButtonCancel->setGeometry(360+x, 320 + y, 81, 31);
        ui->pushButtonApply->setGeometry(450+x, 320 + y, 81, 31);
    }
}

void MainWindow::sltOnCurrentChanged(QWidget *tab)
{
    if (tab == ui->tabSkinDesign)
    {
        changeMainWindowSize();
    }
}

void MainWindow::sltOnAllSkinItemDoubleClicked(QListWidgetItem *item)
{
    if(curtSkinType.indexOf("local")==-1)
    {
        QString localPath = PREFIX "/share/fcitx-qimpanel/skin/"+ curtSkinType.mid(0,curtSkinType.indexOf("(local)"));
        qDebug()<<localPath;
        QDir *temp = new QDir;
        if(true == temp->exists(localPath + "/skin.ini"))
        {
            QMessageBox::information(this,gettext("tips"),gettext("Sougo Skin does not support preview and edit!"));
        }
        else{
            EditingSkinDialog * editingSkinDialog = new EditingSkinDialog(ui->radioButtonHorizontal->isChecked(),item);
            editingSkinDialog->exec();
            refreshListWidgetAllSkin();
        }
    }
    else{
        QString localPath= qgetenv("HOME") + "/.config/fcitx-qimpanel/skin/"+ curtSkinType.mid(0,curtSkinType.indexOf("(local)"));
        qDebug()<<localPath;
        QDir *temp1 = new QDir;
        if(true == temp1->exists(localPath + "/skin.ini"))
        {
            QMessageBox::information(this,gettext("tips"),gettext("Sougo Skin does not support preview and edit!"));
        }
        else{
            EditingSkinDialog * editingSkinDialog1 = new EditingSkinDialog(ui->radioButtonHorizontal->isChecked(),item);
            editingSkinDialog1->exec();
            refreshListWidgetAllSkin();
        }
    }
}

void MainWindow::on_listWidgetAllSkin_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(listWidgetChangeClearFlag)
        return;
    curtSkinType = current->text();
    if(curtSkinType.indexOf("local")==-1)
    {
        QString localPath = PREFIX "/share/fcitx-qimpanel/skin/"+ curtSkinType.mid(0,curtSkinType.indexOf("(local)"));
        qDebug()<<localPath;
        QDir *temp = new QDir;
        if(true == temp->exists(localPath + "/skin.ini"))
        {
            QMessageBox::information(this,gettext("tips"),gettext("Sougo Skin does not support preview and edit!"));
        }
        else{
            setSkinBase();
        }
    }
    else{
        QString localPath= qgetenv("HOME") + "/.config/fcitx-qimpanel/skin/"+ curtSkinType.mid(0,curtSkinType.indexOf("(local)"));
        qDebug()<<localPath;
        QDir *temp1 = new QDir;
        if(true == temp1->exists(localPath + "/skin.ini"))
        {
            QMessageBox::information(this,gettext("tips"),gettext("Sougo Skin does not support preview and edit!"));
        }
        else{
            setSkinBase();
        }
    }

    ui->comboBoxSkinType->setCurrentIndex(ui->listWidgetAllSkin->currentRow());//感觉如果加入其它皮肤会出bug
}

void MainWindow::searchAndSetSystemSkin()
{
    skinPath = FCITXSKINSYSTEM_PATH;
    int count = 0;
    QDir skinDir;
    QFileInfoList list;
    QFileInfoList::Iterator iter;
    skinDir = QDir(skinPath);
    systemSkin_list.clear();
    if (!skinDir.exists())
        return;

    skinDir.setFilter(QDir::Dirs);
    list = skinDir.entryInfoList();
    for (iter = list.begin(); iter != list.end(); ++ iter) {
        if (iter->isDir() && "." != iter->fileName() && ".." != iter->fileName()) {
            QFile fcitxSkinConfFile_conf(iter->absoluteFilePath() + "/fcitx_skin.conf");
            QFile fcitxSkinConfFile_ini(iter->absoluteFilePath() + "/skin.ini");
            if (!fcitxSkinConfFile_conf.exists()&&!fcitxSkinConfFile_ini.exists())
                continue;

            SkinTypeEntry entry;
            entry.name = iter->fileName();
            entry.absolutePath = iter->absoluteFilePath();
            //allSkinType.append(entry);

            if (curtSkinType == entry.name)
            {
                idx = count;
            }

//            ui->comboBoxSkinType->addItem(entry.name);
            systemSkin_list.append(entry.name);
//            ui->listWidgetAllSkin->addItem(entry.name);
            count ++;
        }
    }
//    ui->listWidgetAllSkin->setCurrentRow(idx);
//    ui->comboBoxSkinType->setCurrentIndex(idx);
}

void MainWindow::searchAndSetLocalSkin()
{
    int idx = 0;
    int count = 0;
    QDir skinDir;
    QFileInfoList list;
    QFileInfoList::Iterator iter;
    skinDir = QDir(localPath);
    localSkin_list.clear();
    if (!skinDir.exists())
    {
        qDebug()<<localPath;
        return;
    }
    skinDir.setFilter(QDir::Dirs);
    list = skinDir.entryInfoList();
    for (iter = list.begin(); iter != list.end(); ++ iter) {
        if (iter->isDir() && "." != iter->fileName() && ".." != iter->fileName()) {
            QFile fcitxSkinConfFile_conf(iter->absoluteFilePath() + "/fcitx_skin.conf");
            QFile fcitxSkinConfFile_ini(iter->absoluteFilePath() + "/skin.ini");
            if (!fcitxSkinConfFile_conf.exists()&&!fcitxSkinConfFile_ini.exists())
                continue;

            SkinTypeEntry entry;
            entry.name = iter->fileName();
            entry.absolutePath = iter->absoluteFilePath();

            if (curtSkinType == entry.name)
            {
                idx = count;
            }

            if(ui->listWidgetAllSkin)
            localSkin_list.append(entry.name+"(local)");
//            ui->listWidgetAllSkin->addItem(entry.name+"(local)");
            count ++;
        }
    }
//    ui->listWidgetAllSkin->setCurrentRow(idx);
}

void MainWindow::loadSkinPreview()
{
    qDebug()<<"MainWindow::loadSkinPreview";
    setSkinBase();
}

void MainWindow::loadMainConf()
{
    bool verticalList;
    //QString curtSkinType;

    mSettings->beginGroup("base");
    verticalList = mSettings->value("VerticalList", false).toBool();
    curtSkinType = mSettings->value("CurtSkinType", "ubuntukylin-dark1").toString();
    mSettings->endGroup();

    ui->radioButtonVertical->setChecked(verticalList);
    ui->radioButtonHorizontal->setChecked(!verticalList);
    searchAndSetLocalSkin();
    searchAndSetSystemSkin();
    showListWidgetAllSkin();
    loadSkinPreview();
}
void MainWindow::saveMainConf()
{
    qDebug()<<"MainWindow::saveMainConf";
    bool verticalList;

    mSettings->beginGroup("base");
    verticalList = ui->radioButtonVertical->isChecked();
    curtSkinType = ui->comboBoxSkinType->currentText();
    qDebug()<<"MainWindow::saveMainConf()"<<curtSkinType;
    if(curtSkinType.indexOf("(local)")!=-1)
    {
      curtSkinType = curtSkinType.mid(0,curtSkinType.indexOf("(local)"));
    }
    mSettings->setValue("VerticalList", verticalList);
    mSettings->setValue("CurtSkinType", curtSkinType);
    qDebug()<<"MainWindow::saveMainConf()"<<curtSkinType;
    mSettings->endGroup();
}

void MainWindow::setSkinBase()
{
    SkinFcitx* skin = new SkinFcitx;
    mLayout->removeWidget(qmlView);
    if(curtSkinType.indexOf("(local)")==-1)
    {
        skin->loadSkin(skinPath + curtSkinType + "/");
    }
    else
    {
        skin->loadSkin(localPath + curtSkinType.mid(0,curtSkinType.indexOf("(local)")) + "/");
    }

    if (mSkinFcitx != skin)
       delete mSkinFcitx;
    mSkinFcitx = skin;
#ifdef IS_QT_5
    qmlView->setAttribute(Qt::WA_AlwaysStackOnTop);
    qmlView->setClearColor(Qt::transparent);
    qmlView->rootContext()->setContextProperty("mainSkin", mSkinFcitx);//把qt程序暴露到qml
    qmlView->rootContext()->setContextProperty("mainModel", mMainModer);
    qmlView->setSource(QUrl("qrc:/new/prefix1/qt5_main.qml"));
#endif
#ifdef IS_QT_4
    qmlView->rootContext()->setContextProperty("mainSkin", mSkinFcitx);//把qt程序暴露到qml
    qmlView->rootContext()->setContextProperty("mainModel", mMainModer);
    qmlView->setSource(QUrl("qrc:/new/prefix1/qt4_main.qml"));
#endif

    mLayout->addWidget(qmlView);
    mMainModer->emitSigMainWindowSizeChanged();
}

void MainWindow::sltOnPushButtonApply()
{
    saveMainConf();
    static int flag = 0;
    static int timeFlag = QTime::currentTime().second();
    int currentTime = QTime::currentTime().second();
    if((qAbs(currentTime-timeFlag) > 1)||(flag == 0))
    {
        flag ++;
        qDebug()<<"emit sigRestartQimpanel();";
        emit sigRestartQimpanel();
    }
     timeFlag = QTime::currentTime().second();
}

void MainWindow::sltOnPushButtonCancel()
{
    this->close();
}

void MainWindow::on_radioButtonHorizontal_toggled(bool checked)
{
    mMainModer->setIsHorizontal(checked);
    setSkinBase();
    changeMainWindowSize();
}

void MainWindow::showListWidgetAllSkin()
{
    QList<QString>::Iterator iter_system;
    QList<QString>::Iterator iter_local;
    QString tmp_systemList;
    QString tmp_localList;
    bool flag = true;//
    for (iter_system = systemSkin_list.begin(); iter_system != systemSkin_list.end(); ++ iter_system) {
        tmp_systemList = *iter_system;
        for(iter_local = localSkin_list.begin(); iter_local != localSkin_list.end(); ++ iter_local){
            tmp_localList = *iter_local;
            if(tmp_localList.mid(0,tmp_localList.indexOf("(local)")) == tmp_systemList){
                ui->listWidgetAllSkin->addItem(tmp_localList);
                ui->comboBoxSkinType->addItem(tmp_localList.mid(0,tmp_localList.indexOf("(local)")));
                qDebug()<<tmp_localList;
                 flag = false;
                 continue;
            }
        }
        if(flag)
        {
            qDebug()<<tmp_systemList;
            ui->listWidgetAllSkin->addItem(tmp_systemList);
            ui->comboBoxSkinType->addItem(tmp_systemList);
        }
        flag = true;
    }
        ui->comboBoxSkinType->setCurrentIndex(idx);
        ui->listWidgetAllSkin->setCurrentRow(idx);
}

void MainWindow::refreshListWidgetAllSkin()
{
    disconnect(ui->listWidgetAllSkin, SIGNAL(itemDoubleClicked(QListWidgetItem*)),0, 0);
    listWidgetChangeClearFlag=true;
    ui->listWidgetAllSkin->clear();
    listWidgetChangeClearFlag=false;
    connect(ui->listWidgetAllSkin, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(sltOnAllSkinItemDoubleClicked(QListWidgetItem*)));
    searchAndSetLocalSkin();
    searchAndSetSystemSkin();
    ui->comboBoxSkinType->clear();
    showListWidgetAllSkin();
    qDebug()<<"MainWindow::refreshListWidgetAllSkin()";
}

void MainWindow::setListWidgetAllSkinIndex(int index)
{
    if(index<0)
        return ;
    ui->listWidgetAllSkin->setCurrentRow(index);
}

void MainWindow::linkQtDbusServer()
{
    myInterface = new QDBusInterface("com.fcitx_qimpanel.hotel",
                               "/",
                               "com.fcitx_qimpanel.hotel",
                               QDBusConnection::sessionBus());
    if(!myInterface->isValid())
    {
        qDebug()<< qPrintable(QDBusConnection::sessionBus().lastError().message());
    }
    else{
        QObject::connect(this,SIGNAL(sigRestartQimpanel()),myInterface,SLOT(qtDbusSot_restartQimpanel()));
    }

    //    QDBusMessage m = QDBusMessage::createMethodCall("com.fcitx_qimpanel.hotel",
    //                                                  "/",
    //                                                  "com.fcitx_qimpanel.hotel",
    //                                                  "selectCandidate");
    //    m << 8;
    //    QDBusMessage response = QDBusConnection::sessionBus().call(m);
    //    // 判断Method是否被正确返回
    //    if (response.type() == QDBusMessage::ReplyMessage) {
    //            // QDBusMessage的arguments不仅可以用来存储发送的参数，也用来存储返回值;
    //            // 这里取得checkIn的返回值
    //            int num_room = response.arguments().takeFirst().toInt();
    //            printf("Got %d %s\n", num_room, (num_room > 1) ? "rooms" : "room");
    //    } else {
    //            fprintf(stderr, "Check In fail!\n");
    //    }
}
