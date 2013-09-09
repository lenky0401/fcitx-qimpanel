
#include <QDebug>
#include "skinbase.h"

SkinBase::SkinBase()
{
    mInputBackImg = "";
    mMarginLeft = 0;
    mMarginRight = 0;
    mMarginTop = 0;
    mMarginBottom = 0;
    mInputPos = 0;
    mOutputPos = 0;
    mBackArrowImg = "";
    mForwardArrowImg = "";
    mFontSize = 0;
    mInputColor = QColor(0, 0, 0, 0);
    mIndexColor = QColor(0, 0, 0, 0);
    mFirstCandColor = QColor(0, 0, 0, 0);
    mOtherColor = QColor(0, 0, 0, 0);
}

SkinBase::~SkinBase()
{

}

bool SkinBase::loadSkin(const QString skinPath)
{

}

QColor SkinBase::value2color(const QString& value)
{
    QStringList list = value.split(' ');
    int r = list.at(0).toInt();
    int g = list.at(1).toInt();
    int b = list.at(2).toInt();
    return QColor(r, g, b);
}

void SkinBase::setInputBackImg(const QString inputBackImg)
{
    mInputBackImg = inputBackImg;
    emit inputBackImgChanged();
}

QString SkinBase::inputBackImg() const
{
    return mInputBackImg;
}

void SkinBase::setMarginLeft(const int marginLeft)
{
    mMarginLeft = marginLeft;
    emit marginLeftChanged();
}

int SkinBase::marginLeft() const
{
    return mMarginLeft;
}

void SkinBase::setMarginRight(const int marginRight)
{
    mMarginRight = marginRight;
    emit marginRightChanged();
}

int SkinBase::marginRight() const
{
    return mMarginRight;
}

void SkinBase::setMarginTop(const int marginTop)
{
    mMarginTop = marginTop;
    emit marginTopChanged();
}

int SkinBase::marginTop() const
{
    return mMarginTop;
}

void SkinBase::setMarginBottom(const int marginBottom)
{
    mMarginBottom = marginBottom;
    emit marginBottomChanged();
}

int SkinBase::marginBottom() const
{
    return mMarginBottom;
}

void SkinBase::setInputPos(const int inputPos)
{
    mInputPos = inputPos;
    emit inputPosChanged();
}

int SkinBase::inputPos() const
{
    return mInputPos;
}

void SkinBase::setOutputPos(const int outputPos)
{
    mOutputPos = outputPos;
    emit outputPosChanged();
}

int SkinBase::outputPos() const
{
    return mOutputPos;
}

void SkinBase::setBackArrowImg(const QString backArrowImg)
{
    mBackArrowImg = backArrowImg;
    emit backArrowImgChanged();
}

QString SkinBase::backArrowImg() const
{
    return mBackArrowImg;
}

void SkinBase::setForwardArrowImg(const QString forwardArrowImg)
{
    mForwardArrowImg = forwardArrowImg;
    emit forwardArrowImgChanged();
}

QString SkinBase::forwardArrowImg() const
{
    return mForwardArrowImg;
}

void SkinBase::setFontSize(const int fontSize)
{
    mFontSize = fontSize;
    emit fontSizeChanged();
}

int SkinBase::fontSize() const
{
    return mFontSize;
}

void SkinBase::setInputColor(const QColor inputColor)
{
    mInputColor = inputColor;
    emit inputColorChanged();
}

QColor SkinBase::inputColor() const
{
    return mInputColor;
}

void SkinBase::setIndexColor(const QColor indexColor)
{
    mIndexColor = indexColor;
    emit indexColorChanged();
}

QColor SkinBase::indexColor() const
{
    return mIndexColor;
}

void SkinBase::setFirstCandColor(const QColor firstCandColor)
{
    mFirstCandColor = firstCandColor;
    emit fontSizeChanged();
}

QColor SkinBase::firstCandColor() const
{
    return mFirstCandColor;
}

void SkinBase::setOtherColor(const QColor otherColor)
{
    mOtherColor = otherColor;
    emit otherColorChanged();
}

QColor SkinBase::otherColor() const
{
    return mOtherColor;
}


