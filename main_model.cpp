#include <QDebug>
#include "main_model.h"
#include "candidate_word.h"

MainModel::MainModel()
{

}

MainModel::~MainModel()
{

}

void MainModel::resetData() {
    KimpanelLookupTable lookup_table;
    setCandidateWords(lookup_table);
    setInputString("");
    setHasPrev(false);
    setHasNext(false);
    setInputStringCursorPos(-1);
    setHighLight(-1);
    setIsHorizontal(true);
    setShowTips(false);
    setShowPreedit(false);
    setShowLookupTable(false);
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

void MainModel::setCandidateWords(const KimpanelLookupTable &lookup_table) {
    CandidateWord *candidate;
    QList<KimpanelLookupTable::Entry>::iterator iter;
    QList<KimpanelLookupTable::Entry> entries = lookup_table.entries;

    qDeleteAll(mCandidateWords);
    mCandidateWords.clear();
    for (iter = entries.begin(); iter != entries.end(); ++ iter) {
        if ((candidate = new (std::nothrow)CandidateWord) == NULL)
            break;

        candidate->setCddLabel(iter->label);
        candidate->setCddText(iter->text);
        mCandidateWords.append(candidate);
    }

    setHasPrev(lookup_table.has_prev);
    setHasNext(lookup_table.has_next);

    emit candidateWordsChanged();
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
    emit isHorizontalChanged();
}

bool MainModel::isHorizontal() const {
    return mIsHorizontal;
}

void MainModel::setShowTips(const bool showTips) {
    mShowTips = showTips;
    emit showTipsChanged();
}

bool MainModel::showTips() const {
    return mShowTips;
}

void MainModel::setShowPreedit(const bool showPreedit) {
    mShowPreedit = showPreedit;
    emit showPreeditChanged();
}

bool MainModel::showPreedit() const {
    return mShowPreedit;
}

void MainModel::setShowLookupTable(const bool showLookupTable) {
    mShowLookupTable = showLookupTable;
    emit showLookupTableChanged();
}

bool MainModel::showLookupTable() const {
    return mShowLookupTable;
}
