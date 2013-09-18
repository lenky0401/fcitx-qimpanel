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

#ifndef __CANDIDATE_WORD_H__
#define __CANDIDATE_WORD_H__

#include <QDeclarativeView>
#include <QObject>
#include <qdeclarative.h>

class CandidateWord : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString cddLabel READ cddLabel WRITE setCddLabel
        NOTIFY cddLabelChanged)
    Q_PROPERTY(QString cddText READ cddText WRITE setCddText
        NOTIFY cddTextChanged)

public:
    void setCddLabel(const QString label);
    QString cddLabel() const;
    void setCddText(const QString text);
    QString cddText() const;

signals:
    void cddLabelChanged();
    void cddTextChanged();

private:
    QString mCddLabel;  //存放标号字符串，比如“1.”，“2.”，“3.”，“4.”，“5.”
    QString mCddText;   //存放候选词字符串，比如“啊”，“阿”，“吖”，“呵”，“腌”
};


#endif // __CANDIDATE_WORD_H__
