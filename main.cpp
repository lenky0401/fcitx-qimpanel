#include <QApplication>
#include <QApplication>
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QtDeclarative>
#include <QTextCodec>
#include <QTranslator>
#include "main_controller.h"

#define BUFF_SIZE (512)
typedef void (*sighandler_t) (int);

void init_as_daemon()
{
    pid_t pid;
    if ((pid = fork()) > 0) {
        waitpid(pid, NULL, 0);
        exit(0);
    }
    setsid();
    sighandler_t oldint = signal(SIGINT, SIG_IGN);
    sighandler_t oldhup  =signal(SIGHUP, SIG_IGN);
    sighandler_t oldquit = signal(SIGQUIT, SIG_IGN);
    sighandler_t oldpipe = signal(SIGPIPE, SIG_IGN);
    sighandler_t oldttou = signal(SIGTTOU, SIG_IGN);
    sighandler_t oldttin = signal(SIGTTIN, SIG_IGN);
    sighandler_t oldchld = signal(SIGCHLD, SIG_IGN);
    if (fork() > 0)
        exit(0);
    chdir("/");

    signal(SIGINT, oldint);
    signal(SIGHUP, oldhup);
    signal(SIGQUIT, oldquit);
    signal(SIGPIPE, oldpipe);
    signal(SIGTTOU, oldttou);
    signal(SIGTTIN, oldttin);
    signal(SIGCHLD, oldchld);
}


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

    init_as_daemon();

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

