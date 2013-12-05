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

#ifndef __SKIN_SOGOU_H__
#define __SKIN_SOGOU_H__

#include <QColor>
#include "skinbase.h"

class SkinSogou : public SkinBase
{
public:
    SkinSogou();
    virtual ~SkinSogou();
    virtual bool loadSkin(const QString skinPath);
private:
    QString mCustomImgH1[8];
    int mCustomCntH1;
    QString mCustomImgV1[8];
    int mCustomCntV1;
};

#endif // __SKIN_SOGOU_H__
