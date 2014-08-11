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

#ifndef __SKIN_BASE_H__
#define __SKIN_BASE_H__

#include <QColor>
#include <QFont>
#include <QPixmap>
#include <QRegion>
#include <QDeclarativeView>
#include <QObject>
#include <qdeclarative.h>

class SkinBase : public QObject
{
    Q_OBJECT
    //SkinInfo
    Q_PROPERTY(QString skinName READ skinName WRITE setSkinName
        NOTIFY skinNameChanged)
    Q_PROPERTY(QString skinVersion READ skinVersion WRITE setSkinVersion
        NOTIFY skinVersionChanged)
    Q_PROPERTY(QString skinAuthor READ skinAuthor WRITE setSkinAuthor
        NOTIFY skinAuthorChanged)

    //SkinInputBar
    Q_PROPERTY(QString inputBackImg READ inputBackImg WRITE setInputBackImg
        NOTIFY inputBackImgChanged)
    Q_PROPERTY(QString tipsImg READ tipsImg WRITE setTipsImg
        NOTIFY tipsImgChanged)
    Q_PROPERTY(int marginLeft READ marginLeft WRITE setMarginLeft
        NOTIFY marginLeftChanged)
    Q_PROPERTY(int marginRight READ marginRight WRITE setMarginRight
        NOTIFY marginRightChanged)
    Q_PROPERTY(int marginTop READ marginTop WRITE setMarginTop
        NOTIFY marginTopChanged)
    Q_PROPERTY(int marginBottom READ marginBottom WRITE setMarginBottom
        NOTIFY marginBottomChanged)
    Q_PROPERTY(QString backArrowImg READ backArrowImg WRITE setBackArrowImg
        NOTIFY backArrowImgChanged)
    Q_PROPERTY(QString forwardArrowImg READ forwardArrowImg WRITE setForwardArrowImg
        NOTIFY forwardArrowImgChanged)

    Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize
        NOTIFY fontSizeChanged)
    Q_PROPERTY(int candFontSize READ candFontSize WRITE setCandFontSize
        NOTIFY candFontSizeChanged)
    Q_PROPERTY(QColor inputColor READ inputColor WRITE setInputColor
        NOTIFY inputColorChanged)
    Q_PROPERTY(QColor indexColor READ indexColor WRITE setIndexColor
        NOTIFY indexColorChanged)
    Q_PROPERTY(QColor firstCandColor READ firstCandColor WRITE setFirstCandColor
        NOTIFY firstCandColorChanged)
    Q_PROPERTY(QColor otherColor READ otherColor WRITE setOtherColor
        NOTIFY otherColorChanged)

public:
    //SkinInfo
    void setSkinName(const QString skinName);
    QString skinName()const;
    void setSkinVersion(const QString skinVersion);
    QString skinVersion() const;
    void setSkinAuthor(const QString skinAuthor);
    QString skinAuthor() const;
    //SkinInputBar
    void setInputBackImg(const QString inputBackImg);
    QString inputBackImg() const;
    void setTipsImg(const QString tipsImg);
    QString tipsImg() const;
    void setMarginLeft(const int marginLeft);
    int marginLeft() const;
    void setMarginRight(const int marginRight);
    int marginRight() const;
    void setMarginTop(const int marginTop);
    int marginTop() const;
    void setMarginBottom(const int marginBottom);
    int marginBottom() const;
    void setBackArrowImg(const QString backArrowImg);
    QString backArrowImg() const;
    void setForwardArrowImg(const QString forwardArrowImg);
    QString forwardArrowImg() const;
    void setFontSize(const int fontSize);
    int fontSize() const;
    void setCandFontSize(const int candFontSize);
    int candFontSize() const;
    void setInputColor(const QColor inputColor);
    QColor inputColor() const;
    void setIndexColor(const QColor indexColor);
    QColor indexColor() const;
    void setFirstCandColor(const QColor firstCandColor);
    QColor firstCandColor() const;
    void setOtherColor(const QColor otherColor);
    QColor otherColor() const;

signals:
    void skinNameChanged();
    void skinVersionChanged();
    void skinAuthorChanged();

    void inputBackImgChanged();
    void tipsImgChanged();
    void marginLeftChanged();
    void marginRightChanged();
    void marginTopChanged();
    void marginBottomChanged();
    void backArrowImgChanged();
    void forwardArrowImgChanged();
    void fontSizeChanged();
    void candFontSizeChanged();
    void inputColorChanged();
    void indexColorChanged();
    void firstCandColorChanged();
    void otherColorChanged();

private:
    //Fcitx SkinInfo
    QString mSkinName;
    QString mSkinVersion;
    QString mSkinAuthor;
    QString mSkinDesc;

    //Fcitx SkinInputBar
    QString mInputBackImg;
    QString mTipsImg;
    int mMarginLeft;
    int mMarginRight;
    int mMarginTop;
    int mMarginBottom;
    QString mBackArrowImg;
    QString mForwardArrowImg;

    //Fcitx SkinFont
    int mFontSize;
    int mCandFontSize;
    QColor mInputColor;
    QColor mIndexColor;
    QColor mFirstCandColor;
    QColor mOtherColor;

public:
    Q_PROPERTY(int inputStringPosX READ inputStringPosX WRITE setInputStringPosX
            NOTIFY inputStringPosXChanged)
    void setInputStringPosX(const int inputStringPosX);
    int inputStringPosX() const;
signals:
    void inputStringPosXChanged();
private:
    int mInputStringPosX;

public:
    Q_PROPERTY(int inputStringPosY READ inputStringPosY WRITE setInputStringPosY
            NOTIFY inputStringPosYChanged)
    void setInputStringPosY(const int inputStringPosY);
    int inputStringPosY() const;
signals:
    void inputStringPosYChanged();
private:
    int mInputStringPosY;

public:
    Q_PROPERTY(int outputCandPosX READ outputCandPosX WRITE setOutputCandPosX
            NOTIFY outputCandPosXChanged)
    void setOutputCandPosX(const int outputCandPosX);
    int outputCandPosX() const;
signals:
    void outputCandPosXChanged();
private:
    int mOutputCandPosX;

public:
    Q_PROPERTY(int outputCandPosY READ outputCandPosY WRITE setOutputCandPosY
            NOTIFY outputCandPosYChanged)
    void setOutputCandPosY(const int outputCandPosY);
    int outputCandPosY() const;
signals:
    void outputCandPosYChanged();
private:
    int mOutputCandPosY;

public:
    Q_PROPERTY(int backArrowPosX READ backArrowPosX WRITE setBackArrowPosX
            NOTIFY backArrowPosXChanged)
    void setBackArrowPosX(const int backArrowPosX);
    int backArrowPosX() const;
signals:
    void backArrowPosXChanged();
private:
    int mBackArrowPosX;

public:
    Q_PROPERTY(int backArrowPosY READ backArrowPosY WRITE setBackArrowPosY
            NOTIFY backArrowPosYChanged)
    void setBackArrowPosY(const int backArrowPosY);
    int backArrowPosY() const;
signals:
    void backArrowPosYChanged();
private:
    int mBackArrowPosY;

public:
    Q_PROPERTY(int forwardArrowPosX READ forwardArrowPosX WRITE setForwardArrowPosX
            NOTIFY forwardArrowPosXChanged)
    void setForwardArrowPosX(const int forwardArrowPosX);
    int forwardArrowPosX() const;
signals:
    void forwardArrowPosXChanged();
private:
    int mForwardArrowPosX;

public:
    Q_PROPERTY(int forwardArrowPosY READ forwardArrowPosY WRITE setForwardArrowPosY
            NOTIFY forwardArrowPosYChanged)
    void setForwardArrowPosY(const int forwardArrowPosY);
    int forwardArrowPosY() const;
signals:
    void forwardArrowPosYChanged();
private:
    int mForwardArrowPosY;

public:
    Q_PROPERTY(int adjustWidth READ adjustWidth WRITE setAdjustWidth
            NOTIFY adjustWidthChanged)
    void setAdjustWidth(const int adjustWidth);
    int adjustWidth() const;
signals:
    void adjustWidthChanged();
private:
    int mAdjustWidth;

public:
    Q_PROPERTY(int adjustHeight READ adjustHeight WRITE setAdjustHeight
            NOTIFY adjustHeightChanged)
    void setAdjustHeight(const int adjustHeight);
    int adjustHeight() const;
signals:
    void adjustHeightChanged();
private:
    int mAdjustHeight;

public:
    Q_PROPERTY(QString horizontalTileMode READ horizontalTileMode WRITE setHorizontalTileMode
            NOTIFY horizontalTileModeChanged)
    void setHorizontalTileMode(const QString horizontalTileMode);
    QString horizontalTileMode() const;
signals:
    void horizontalTileModeChanged();
private:
    QString mHorizontalTileMode;

public:
    Q_PROPERTY(QString verticalTileMode READ verticalTileMode WRITE setVerticalTileMode
            NOTIFY verticalTileModeChanged)
    void setVerticalTileMode(const QString verticalTileMode);
    QString verticalTileMode() const;
signals:
    void verticalTileModeChanged();
private:
    QString mVerticalTileMode;

//===================================================================================================
private:
    //Fcitx SkinInputBar
    QString mInputBackImgVertical;
    QString mTipsImgVertical;
    int mMarginLeftVertical;
    int mMarginRightVertical;
    int mMarginTopVertical;
    int mMarginBottomVertical;
    QString mBackArrowImgVertical;
    QString mForwardArrowImgVertical;

    //Fcitx SkinFont
    int mFontSizeVertical;
    int mCandFontSizeVertical;
    QColor mInputColorVertical;
    QColor mIndexColorVertical;
    QColor mFirstCandColorVertical;
    QColor mOtherColorVertical;

    int mInputStringPosXVertical;
    int mInputStringPosYVertical;
    int mOutputCandPosXVertical;
    int mOutputCandPosYVertical;
    int mBackArrowPosXVertical;
    int mBackArrowPosYVertical;
    int mForwardArrowPosXVertical;
    int mForwardArrowPosYVertical;

    int mAdjustWidthVertical;
    int mAdjustHeightVertical;
    QString mHorizontalTileModeVertical;
    QString mVerticalTileModeVertical;

public:
#define DEFINE_SET_PROPERTY(read, type, property) \
    void set##property(const type read);

    DEFINE_SET_PROPERTY(inputBackImgVertical, QString, InputBackImgVertical)
    DEFINE_SET_PROPERTY(tipsImgVertical, QString, TipsImgVertical)
    DEFINE_SET_PROPERTY(marginLeftVertical, int, MarginLeftVertical)

    DEFINE_SET_PROPERTY(marginRightVertical, int, MarginRightVertical)
    DEFINE_SET_PROPERTY(marginTopVertical, int, MarginTopVertical)
    DEFINE_SET_PROPERTY(marginBottomVertical, int, MarginBottomVertical)
    DEFINE_SET_PROPERTY(backArrowImgVertical, QString, BackArrowImgVertical)
    DEFINE_SET_PROPERTY(forwardArrowImgVertical, QString, ForwardArrowImgVertical)
    DEFINE_SET_PROPERTY(fontSizeVertical, int, FontSizeVertical)
    DEFINE_SET_PROPERTY(candFontSizeVertical, int, CandFontSizeVertical)
    DEFINE_SET_PROPERTY(inputColorVertical, QColor, InputColorVertical)
    DEFINE_SET_PROPERTY(indexColorVertical, QColor, IndexColorVertical)
    DEFINE_SET_PROPERTY(firstCandColorVertical, QColor, FirstCandColorVertical)
    DEFINE_SET_PROPERTY(otherColorVertical, QColor, OtherColorVertical)


    DEFINE_SET_PROPERTY(inputStringPosXVertical, int, InputStringPosXVertical)
    DEFINE_SET_PROPERTY(inputStringPosYVertical, int, InputStringPosYVertical)
    DEFINE_SET_PROPERTY(outputCandPosXVertical, int, OutputCandPosXVertical)
    DEFINE_SET_PROPERTY(outputCandPosYVertical, int, OutputCandPosYVertical)
    DEFINE_SET_PROPERTY(backArrowPosXVertical, int, BackArrowPosXVertical)
    DEFINE_SET_PROPERTY(backArrowPosYVertical, int, BackArrowPosYVertical)
    DEFINE_SET_PROPERTY(forwardArrowPosXVertical, int, ForwardArrowPosXVertical)
    DEFINE_SET_PROPERTY(forwardArrowPosYVertical, int, ForwardArrowPosYVertical)

    DEFINE_SET_PROPERTY(adjustWidthVertical, int, AdjustWidthVertical)
    DEFINE_SET_PROPERTY(adjustHeightVertical, int, AdjustHeightVertical)
    DEFINE_SET_PROPERTY(horizontalTileModeVertical, QString, HorizontalTileModeVertical)
    DEFINE_SET_PROPERTY(verticalTileModeVertical, QString, VerticalTileModeVertical)
#undef DEFINE_SET_PROPERTY
//===================================================================================================

public:
    SkinBase();
    virtual ~SkinBase();
    void reloadSkin();
    void init();

protected:
    QColor value2color(const QString& value);
};

#endif //__SKIN_BASE_H__
