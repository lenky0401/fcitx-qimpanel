#include <QApplication>
#include <QApplication>
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QtDeclarative>
#include <QTextCodec>
#include <QTranslator>
#include "main_controller.h"

int main(int argc, char** argv)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    MainController MainController(argc, argv);
    QTranslator translator;
    if (translator.load(QString("zh_CN.qm")) == false)
        qDebug() << "load qm error.";
    MainController.installTranslator(&translator);

    if (!MainController.init()) {
        return -1;
    }
    return MainController.exec();
}

