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

#include <QApplication>
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QtDeclarative>
#include <QTextCodec>
#include <QTranslator>

#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <fcitx-utils/utils.h>

#include "main.h"
#include "main_controller.h"

#define BUFF_SIZE (512)
char sharePath[BUFF_SIZE] = {0};
bool reloadcfg;

#define LOCKFILE "/tmp/fcitx-qimpanel.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
int isRunning()
{
    char buf[16];
    struct flock fl;

    int fd = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
    if (fd < 0) {
        printf("Can not open %s: %s.\n", LOCKFILE, strerror(errno));
        return -1;
    }

    fl.l_type = F_WRLCK;
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;

    if (fcntl(fd, F_SETLK, &fl) < 0) {
        printf("Can not lock %s: %s.\n", LOCKFILE, strerror(errno));
        return -1;
    }

    ftruncate(fd, 0);
    sprintf(buf, "%d", getpid());
    write(fd, buf, strlen(buf));

    return 0;
}

char* getQimpanelSharePath(const char * const fileName)
{
    strcpy(sharePath, "/usr/share/fcitx-qimpanel/");
    strcpy(sharePath + strlen("/usr/share/fcitx-qimpanel/"), fileName);
    printf("%s\n", sharePath);

    return sharePath;
}

void sigRoutine(int sigNum) {
    switch (sigNum) {
    case 1:
        printf("Get a signal -- SIGHUP\n");
        reloadcfg = true;
        break;
    }
    return;
}

int main(int argc, char** argv)
{
    fcitx_utils_init_as_daemon();

    if (isRunning()) {
        exit(1);
    }

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QTranslator translator;
    if (translator.load(QString(getQimpanelSharePath("zh_CN.qm"))) == false)
        qDebug() << "load qm error.";

    signal(SIGHUP, sigRoutine);

    QApplication *app = new QApplication(argc, argv);
    app->installTranslator(&translator);
    app->setApplicationName("fcitx-qimpanel");

    MainController *ctrl = MainController::self();

    reloadcfg = false;
    for (;;) {
        app->processEvents();

        if (reloadcfg) {
            reloadcfg = false;
            MainController::self()->getTrayMenu()->restart();
        }
    }

    delete ctrl;
    delete app;
    return 0;
}

