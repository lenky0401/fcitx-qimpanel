#include <QString>
#include <QDebug>
#include <libintl.h>
#include <QApplication>
#include <qtextstream.h>
#include <QTextCodec>
#include <QTranslator>
#include "mainwindow.h"
#include <QDir>
#include <fcitx-utils/utils.h>

#define FCITXSKIN_PATH (PREFIX "/share/fcitx-qimpanel/skin/")
#define BUFF_SIZE (512)
char sharePath[BUFF_SIZE] = {0};

int main(int argc, char *argv[])
{
    /*
    QTranslator translator;
    QString locale = QLocale::system().name();
    if(locale == "zh_CN") {
       if (translator.load(PREFIX "/share/fcitx-qimpanel/fcitx_skin_zh_CN.qm") == false)
//        if (translator.load(QString(getQimpanelSharePath("fcitx_skin_zh_CN.qm"))) == false)
            qDebug() << "load qm error.";
    }
    */
    QApplication app(argc, argv);
//    app.installTranslator(&translator);
    app.setApplicationName("fcitx-qimpanel-configtool");
    #ifdef IS_QT_5

    #endif
    #ifdef IS_QT_4
        QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
        QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    #endif
    QString localPath = qgetenv("HOME") + "/.config/";
    QDir *temp = new QDir;
    if(false == temp->exists(localPath + "fcitx-qimpanel"))
    {
//        QString cmd = "mkdir " + localPath +"fcitx-qimpanel";
//        QByteArray ba = cmd.toLatin1();
//        const char *transpd = ba.data();
//        if(0!= system(transpd))
//        {
//            return 0;
//        }
        if(!temp->mkdir(localPath + "fcitx-qimpanel"))
            qDebug()<<"mkdir "+localPath + "fcitx-qimpanel fail";
    }

    setlocale(LC_ALL,"");
    bindtextdomain ("fcitx-qimpanel", PREFIX "/share/locale"); //告诉gettext最终的生成的翻译文件mo的位置
    bind_textdomain_codeset("fcitx-qimpanel","UTF-8"); //指定域消息条目(mo)中消息的字符编码
    textdomain("fcitx-qimpanel");//设定翻译环境，即指定使用gettext的翻译。

    QString localPath2 = qgetenv("HOME") + "/.config/fcitx-qimpanel/";
    QDir *temp2 = new QDir;
    if(false == temp2->exists(localPath2 + "skin"))
    {
//        QString cmd2 = "mkdir " + localPath2 +"skin";
//        QByteArray ba2 = cmd2.toLatin1();
//        const char *transpd2 = ba2.data();
//        if(0!= system(transpd2))
//        {
//            return 0 ;
//        }
        if(!temp2->mkdir(localPath2 +"skin"))
            qDebug()<<"mkdir "+localPath2 +"skin fail";
    }

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
