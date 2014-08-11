#include <QString>
#include <QDebug>
#include <QApplication>
#include <QTextCodec>
#include <qtextstream.h>
#include <QTranslator>
#include "mainwindow.h"
#include <QDir>
#include <fcitx-utils/utils.h>

#define FCITXSKIN_PATH "/usr/share/fcitx-qimpanel/skin/ "
#define BUFF_SIZE (512)
char sharePath[BUFF_SIZE] = {0};

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QTranslator translator;
    QString locale = QLocale::system().name();
    if(locale == "zh_CN") {
       if (translator.load("/usr/share/fcitx-qimpanel/fcitx_skin_zh_CN.qm") == false)
    //    if (translator.load(QString(getQimpanelSharePath("fcitx_skin_zh_CN.qm"))) == false)
            qDebug() << "load qm error.";
    }
    QApplication app(argc, argv);
    app.installTranslator(&translator);
    app.setApplicationName("fcitx-qimpanel-configtool");

    QString localPath = qgetenv("HOME") + "/.config/";
    QDir *temp = new QDir;
    if(false == temp->exists(localPath + "fcitx-qimpanel"))
    {
        QString cmd = "mkdir " + localPath +"fcitx-qimpanel";
        QByteArray ba = cmd.toLatin1();
        const char *transpd = ba.data();
        if(0!= system(transpd))
        {
            return 0;
        }
    }

    QString localPath2 = qgetenv("HOME") + "/.config/fcitx-qimpanel/";
    QDir *temp2 = new QDir;
    if(false == temp2->exists(localPath2 + "skin"))
    {
        QString cmd2 = "mkdir " + localPath2 +"skin";
        QByteArray ba2 = cmd2.toLatin1();
        const char *transpd2 = ba2.data();
        if(0!= system(transpd2))
        {
            return 0 ;
        }
    }

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
