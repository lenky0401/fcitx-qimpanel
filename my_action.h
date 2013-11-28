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

#ifndef __MY_ACTION_H__
#define __MY_ACTION_H__

#include <QAction>
#include "kimpanelagent.h"

typedef enum SkinClass
{
    FCITX,
    SOGOU
} SkinClass;

class MyAction : public QAction
{
    Q_OBJECT

public:
    MyAction(const QString &text, QObject *parent);
    MyAction(const QIcon &icon, const QString &text, QObject *parent);
    virtual ~MyAction();

public:
    void setProp(const KimpanelProperty &prop);
    const KimpanelProperty& getProp();
    void setSkinPath(const QString skinPath);
    const QString getSkinPath();
    void setSkinClass(const SkinClass skinClass);
    const SkinClass getSkinClass();

private:

    KimpanelProperty mProp;
    QString mSkinPath;
    SkinClass mSkinClass;
};

#endif // __MY_ACTION_H__
