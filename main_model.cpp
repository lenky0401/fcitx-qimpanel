
#include "main_model.h"
#include "candidate_word.h"

MainModel::MainModel()
{

}

MainModel::~MainModel()
{

}

void MainModel::setInputString(const QString inputString) {
	mInputString = inputString;
	emit inputStringChanged();
}

QString MainModel::inputString() const {
	return mInputString;
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

