
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
    Q_PROPERTY(bool hasPrev READ hasPrev WRITE setHasPrev
        NOTIFY hasPrevChanged)
    Q_PROPERTY(bool hasNext READ hasNext WRITE setHasNext
        NOTIFY hasNextChanged)

    Q_PROPERTY(int highLight READ highLight WRITE setHighLight
        NOTIFY highLightChanged)

public:
    MainModel();
    virtual ~MainModel();

public:
    void setInputString(const QString inputString);
    QString inputString() const;
    void setCandidateWords(const KimpanelLookupTable &lookup_table);
    QDeclarativeListProperty<CandidateWord> candidateWords();
    void setHasPrev(const bool hasPrev);
    bool hasPrev() const;
    void setHasNext(const bool hasNext);
    bool hasNext() const;
    void setInputStringCursorPos(int pos);
    void setHighLight(const int highLight);
    int highLight() const;

signals:
    void inputStringChanged();
    void candidateWordsChanged();
    void hasPrevChanged();
    void hasNextChanged();
    void highLightChanged();

private:
    QString mInputString;
    QList<CandidateWord *> mCandidateWords;
    bool mHasPrev;
    bool mHasNext;
    int mHighLight;

};

#endif // __MAIN_MODEL_H__
