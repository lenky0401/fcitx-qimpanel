
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
    SkinBase();
    virtual ~SkinBase();
    virtual bool loadSkin(const QString skinPath);

protected:
    QColor value2color(const QString& value);
};

#endif //__SKIN_BASE_H__
