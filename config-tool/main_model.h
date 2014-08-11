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

#ifndef __MAIN_MODEL_H__
#define __MAIN_MODEL_H__

#include <QDeclarativeView>
#include <QObject>
#include <qdeclarative.h>
#include "kimpanelagenttype.h"
#include "candidate_word.h"

class MainModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString inputString READ inputString WRITE setInputString 
        NOTIFY inputStringChanged)

    Q_PROPERTY(QString tipsString READ tipsString WRITE setTipsString
        NOTIFY tipsStringChanged)

    Q_PROPERTY(QDeclarativeListProperty<CandidateWord> candidateWords
        READ candidateWords NOTIFY candidateWordsChanged)
    Q_PROPERTY(bool hasPrev READ hasPrev WRITE setHasPrev
        NOTIFY hasPrevChanged)
    Q_PROPERTY(bool hasNext READ hasNext WRITE setHasNext
        NOTIFY hasNextChanged)

    Q_PROPERTY(int highLight READ highLight WRITE setHighLight
        NOTIFY highLightChanged)
    Q_PROPERTY(bool isHorizontal READ isHorizontal WRITE setIsHorizontal
        NOTIFY isHorizontalChanged)

public:
    static MainModel* self();
    virtual ~MainModel();
    void init();

private:
    explicit MainModel();
    static MainModel *mSelf;

public:
    void resetData();
    void setInputStringCursorPos(int pos);

public:
    void setInputString(const QString inputString);
    QString inputString() const;
    void setTipsString(const QString tipsString);
    QString tipsString() const;
    void setCandidateWords();
    QDeclarativeListProperty<CandidateWord> candidateWords();
    void setHasPrev(const bool hasPrev);
    bool hasPrev() const;
    void setHasNext(const bool hasNext);
    bool hasNext() const;
    void setHighLight(const int highLight);
    int highLight() const;
    void setIsHorizontal(const bool isHorizontal);
    bool isHorizontal() const;

    int currentCandidateWordNum(int Num);
    void emitSigMainWindowSizeChanged();

signals:
    void inputStringChanged();
    void tipsStringChanged();
    void candidateWordsChanged();
    void hasPrevChanged();
    void hasNextChanged();
    void highLightChanged();
    void isHorizontalChanged();

    void currentCandidateWordNumChanged();
    void qmlMainWindowSizeChanged();

private:
    QString mInputString;
    QString mTipsString;
    QList<CandidateWord *> mCandidateWords;
    bool mHasPrev;
    bool mHasNext;
    int mHighLight;
    bool mIsHorizontal;
    bool mShowTips;
    bool mShowPreedit;
    bool mShowLookupTable;
    int mCurrentCandidateWordNum;
};

#endif // __MAIN_MODEL_H__
