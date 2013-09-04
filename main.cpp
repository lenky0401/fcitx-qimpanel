#include <QApplication>
#include <QApplication>
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QtDeclarative>
#include <QTextCodec>
#include <QTranslator>

#include <fcitx-utils/utils.h>

#include "main_controller.h"

#define BUFF_SIZE (512)

int main(int argc, char** argv)
{
    char *p;
    char exec_name[BUFF_SIZE];

    memset(exec_name, 0, BUFF_SIZE);
    if (readlink("/proc/self/exe", exec_name, BUFF_SIZE) < 0) {
        perror("readlink");
        exit(EXIT_FAILURE);
    }

    if ((p = strrchr(exec_name, '/')) == NULL) {
        perror("strrchr");
        exit(EXIT_FAILURE);
    }
    strcpy(p + 1, "zh_CN.qm");

    //fcitx_utils_init_as_daemon();

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    MainController MainController(argc, argv);
    QTranslator translator;
    if (translator.load(QString(exec_name)) == false)
        qDebug() << "load qm error.";
    MainController.installTranslator(&translator);

    if (!MainController.init()) {
        return -1;
    }
    return MainController.exec();
}

