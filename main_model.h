
#ifndef __MAIN_MODEL_H__
#define __MAIN_MODEL_H__

#include <QDeclarativeView>
#include <QObject>
#include <qdeclarative.h>
#include "candidate_word.h"
#include "kimpanelagenttype.h"

class MainModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString inputString READ inputString WRITE setInputString 
        NOTIFY inputStringChanged)

    Q_PROPERTY(QDeclarativeListProperty<CandidateWord> candidateWords
        READ candidateWords NOTIFY candidateWordsChanged)


public:
    MainModel();
    virtual ~MainModel();

public:
    void setInputString(const QString inputString);
    QString inputString() const;
    void setCandidateWords(const KimpanelLookupTable &lookup_table);
    QDeclarativeListProperty<CandidateWord> candidateWords();

signals:
    void inputStringChanged();
    void candidateWordsChanged();
private:
    QString mInputString;
    QList<CandidateWord *> mCandidateWords;

};

#endif // __MAIN_MODEL_H__
