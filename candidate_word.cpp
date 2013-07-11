
#include "candidate_word.h"

void CandidateWord::setCddLabel(const QString label) {
    mCddLabel = label;
    emit cddLabelChanged();
}

void CandidateWord::setCddText(const QString text) {
    mCddText = text;
    emit cddTextChanged();
}

QString CandidateWord::cddLabel() const {
    return mCddLabel;
}

QString CandidateWord::cddText() const {
    return mCddText;
}
