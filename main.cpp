#include <QApplication>
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QtDeclarative>
#include <QTextCodec>
#include <QTranslator>

#include <fcitx-utils/utils.h>

#include "main.h"
#include "main_controller.h"

#define BUFF_SIZE (512)
char sharePath[BUFF_SIZE] = {0};

char* getQimpanelSharePath(const char * const fileName)
{
    char *p;
    if (readlink("/proc/self/exe", sharePath, BUFF_SIZE) < 0) {
        perror("readlink");
        exit(EXIT_FAILURE);
    }

    if ((p = strrchr(sharePath, '/')) == NULL) {
        perror("strrchr");
        exit(EXIT_FAILURE);
    }
    *p = '0';

    if ((p = strrchr(sharePath, '/')) == NULL) {
        perror("strrchr");
        exit(EXIT_FAILURE);
    }
    strcpy(p + 1, "share/fcitx-qimpanel/");
    strcpy(p + 1 + strlen("share/fcitx-qimpanel/"), fileName);

    return sharePath;
}

int main(int argc, char** argv)
{
    fcitx_utils_init_as_daemon();

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QTranslator translator;
    if (translator.load(QString(getQimpanelSharePath("zh_CN.qm"))) == false)
        qDebug() << "load qm error.";

    QApplication *app = new QApplication(argc, argv);
    app->installTranslator(&translator);
    app->setApplicationName("fcitx-qimpanel");

    MainController *ctrl = MainController::self();

    int ret = app->exec();

    delete ctrl;
    delete app;
    qDebug() << ret;
    return ret;
}

