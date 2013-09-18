/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  lenky gao    lenky0401@gmail.com
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

