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

#include "candidate_word.h"
#include <QDebug>

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
