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
char execPath[BUFF_SIZE] = {0};

char* getExecPath(const char * const fileName)
{
    char *p;
    if (readlink("/proc/self/exe", execPath, BUFF_SIZE) < 0) {
        perror("readlink");
        exit(EXIT_FAILURE);
    }

    if ((p = strrchr(execPath, '/')) == NULL) {
        perror("strrchr");
        exit(EXIT_FAILURE);
    }
    strcpy(p + 1, fileName);

    return execPath;
}

int main(int argc, char** argv)
{

    //fcitx_utils_init_as_daemon();

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QTranslator translator;
    if (translator.load(QString(getExecPath("zh_CN.qm"))) == false)
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

