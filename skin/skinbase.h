
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
    Q_PROPERTY(int inputPos READ inputPos WRITE setInputPos
        NOTIFY inputPosChanged)
    Q_PROPERTY(int outputPos READ outputPos WRITE setOutputPos
        NOTIFY outputPosChanged)
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
    void setInputPos(const int inputPos);
    int inputPos() const;
    void setOutputPos(const int outputPos);
    int outputPos() const;
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
    void inputPosChanged();
    void outputPosChanged();
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
    int mInputPos;
    int mOutputPos;
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
    SkinBase();
    virtual ~SkinBase();
    virtual bool loadSkin(const QString skinPath);

protected:
    QColor value2color(const QString& value);
};

#endif //__SKIN_BASE_H__
