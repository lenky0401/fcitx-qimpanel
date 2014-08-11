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

#include <QDebug>
#include "main_model.h"
#include "candidate_word.h"

MainModel* MainModel::mSelf = 0;

MainModel* MainModel::self()
{
    if (!mSelf) {
        mSelf = new MainModel;
    }
    return mSelf;
}

MainModel::MainModel()
{
    mCurrentCandidateWordNum = 5; //默认为5
    setIsHorizontal(true);
}

MainModel::~MainModel()
{

}

void MainModel::resetData() {
    setCandidateWords();
    setInputString("");
    setHasPrev(false);
    setHasNext(false);
    setInputStringCursorPos(-1);
    setHighLight(-1);
    //这个不属于焦点切换时需要重置的值
}

void MainModel::setInputString(const QString inputString) {
    mInputString = inputString;
    emit inputStringChanged();
}

QString MainModel::inputString() const {
    return mInputString;
}

void MainModel::setTipsString(const QString tipsString) {
    mTipsString = tipsString;
    emit tipsStringChanged();
    emit qmlMainWindowSizeChanged();
}

QString MainModel::tipsString() const {
    return mTipsString;
}

void MainModel::setInputStringCursorPos(int pos) {
    setInputString(mInputString.insert(pos, QString("|")));
}

void candidateWordsPropAppend(QDeclarativeListProperty<CandidateWord>* prop, CandidateWord* value)
{
    Q_UNUSED(prop);
    Q_UNUSED(value);
    return; //Append not supported
}

int candidateWordsPropCount(QDeclarativeListProperty<CandidateWord>* prop)
{
    return static_cast<QList<CandidateWord*>*>(prop->data)->count();
}

CandidateWord* candidateWordsPropAt(QDeclarativeListProperty<CandidateWord>* prop, int index)
{
    return static_cast<QList<CandidateWord*>*>(prop->data)->at(index);
}

void MainModel::setCandidateWords() {
    CandidateWord *candidate;
    QStringList label;
    QStringList text;
    int i = 0;
    switch (mCurrentCandidateWordNum) {
    case 1:
        label.append("1.");
        text.append("你好");
        break;
    case 2:
        label.append("1.");
        text.append("你好");
        label.append("2.");
        text.append("你");
        break;
    case 3:
        label.append("1.");
        text.append("你好");
        label.append("2.");
        text.append("你");
        label.append("3.");
        text.append("拟");
        break;
    case 4:
        label.append("1.");
        text.append("你好");
        label.append("2.");
        text.append("你");
        label.append("3.");
        text.append("拟");
        label.append("4.");
        text.append("尼");
        break;
    case 5:
        label.append("1.");
        text.append("你好");
        label.append("2.");
        text.append("你");
        label.append("3.");
        text.append("拟");
        label.append("4.");
        text.append("尼");
        label.append("5.");
        text.append("呢");
        break;
    case 6:
        label.append("1.");
        text.append("你好");
        label.append("2.");
        text.append("你");
        label.append("3.");
        text.append("拟");
        label.append("4.");
        text.append("尼");
        label.append("5.");
        text.append("呢");
        label.append("6.");
        text.append("泥");
        break;
    case 7:
        label.append("1.");
        text.append("你好");
        label.append("2.");
        text.append("你");
        label.append("3.");
        text.append("拟");
        label.append("4.");
        text.append("尼");
        label.append("5.");
        text.append("呢");
        label.append("6.");
        text.append("泥");
        label.append("7.");
        text.append("妳");
        break;
    case 8:
        label.append("1.");
        text.append("你好");
        label.append("2.");
        text.append("你");
        label.append("3.");
        text.append("拟");
        label.append("4.");
        text.append("尼");
        label.append("5.");
        text.append("呢");
        label.append("6.");
        text.append("泥");
        label.append("7.");
        text.append("妳");
        label.append("8.");
        text.append("妮");
        break;
    case 9:
        label.append("1.");
        text.append("你好");
        label.append("2.");
        text.append("你");
        label.append("3.");
        text.append("拟");
        label.append("4.");
        text.append("尼");
        label.append("5.");
        text.append("呢");
        label.append("6.");
        text.append("泥");
        label.append("7.");
        text.append("妳");
        label.append("8.");
        text.append("妮");
        label.append("9.");
        text.append("腻");
        break;
    case 10:
        label.append("1.");
        text.append("你好");
        label.append("2.");
        text.append("你");
        label.append("3.");
        text.append("拟");
        label.append("4.");
        text.append("尼");
        label.append("5.");
        text.append("呢");
        label.append("6.");
        text.append("泥");
        label.append("7.");
        text.append("妳");
        label.append("8.");
        text.append("妮");
        label.append("9.");
        text.append("腻");
        label.append("0.");
        text.append("逆");
        break;
    default:
        break;
    }

    qDeleteAll(mCandidateWords);
    mCandidateWords.clear();

    for(i=0;i<label.length();i++)
    {
        if ((candidate = new (std::nothrow)CandidateWord) == NULL)
            break;
        candidate->setCddLabel(label.at(i));
        candidate->setCddText(text.at(i));
        mCandidateWords.append(candidate);
    }
    emit candidateWordsChanged();
    emit qmlMainWindowSizeChanged();
}

QDeclarativeListProperty<CandidateWord> MainModel::candidateWords() {

    return QDeclarativeListProperty<CandidateWord>(this, &mCandidateWords, &candidateWordsPropAppend,
        &candidateWordsPropCount, &candidateWordsPropAt, 0);
}

void MainModel::setHasPrev(const bool hasPrev) {
    mHasPrev = hasPrev;
    emit hasPrevChanged();
}

bool MainModel::hasPrev() const {
    return mHasPrev;
}

void MainModel::setHasNext(const bool hasNext) {
    mHasNext = hasNext;
    emit hasNextChanged();
}

bool MainModel::hasNext() const {
    return mHasNext;
}

void MainModel::setHighLight(const int highLight) {
    mHighLight = highLight;
    emit highLightChanged();
}

int MainModel::highLight() const {
    return mHighLight;
}

void MainModel::setIsHorizontal(const bool isHorizontal) {
    mIsHorizontal = isHorizontal;
    emit qmlMainWindowSizeChanged();
}
bool MainModel::isHorizontal() const {
    return mIsHorizontal;
}

void MainModel::emitSigMainWindowSizeChanged()
{
       emit qmlMainWindowSizeChanged();
}














