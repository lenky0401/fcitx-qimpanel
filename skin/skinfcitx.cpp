#include <QDebug>
#include <QBitmap>
#include <QColor>
#include <QDir>
#include <QFile>
#include <QFontMetrics>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QTextStream>

#include "skinfcitx.h"

SkinFcitx::SkinFcitx() : SkinBase()
{

}

SkinFcitx::~SkinFcitx()
{

}

bool SkinFcitx::loadSkin(const QString skinPath)
{
    QFile fcitxSkinConfFile(skinPath + "fcitx_skin.conf");
    if (!fcitxSkinConfFile.exists())
        return false;

    if (!fcitxSkinConfFile.open(QIODevice::ReadOnly))
        return false;

    QString line;
    QString key, value;

    bool skinFont = false;
    bool skinInputBar = false;
    bool skinFontVertical = false;
    bool skinInputBarVertical = false;

    QTextStream textStream(fcitxSkinConfFile.readAll());

    do {
        line = textStream.readLine();

        if (line.isEmpty() || line.at(0) == '#')
            continue;

        if (line.at(0) == '[') {
            skinFont = (line == "[SkinFont]");
            skinInputBar = (line == "[SkinInputBar]");
            skinFontVertical = (line == "[SkinFontVertical]");
            skinInputBarVertical = (line == "[SkinInputBarVertical]");
            continue;
        }

        if (!line.contains('='))
            continue;

        key = line.split('=').at(0);
        value = line.split('=').at(1);

        if (value.isEmpty())
            continue;

        if (skinFont) {
            if (key == "FontSize") {
                setFontSize(value.toInt());

            } else if (key == "CandFontSize") {
                setCandFontSize(value.toInt());

            } else if (key == "InputColor") {
                setInputColor(value2color(value));

            } else if (key == "IndexColor") {
                setIndexColor(value2color(value));

            } else if (key == "FirstCandColor") {
                setFirstCandColor(value2color(value));

            } else if (key == "OtherColor") {
                setOtherColor(value2color(value));

            }
        } else if (skinInputBar) {
            if (key == "BackImg") {
                setInputBackImg("file:/" + skinPath + value);

            } else if (key == "TipsImg") {
                setTipsImg("file:/" + skinPath + value);

            } else if (key == "MarginLeft") {
                setMarginLeft(value.toInt());

            } else if (key == "MarginTop") {
                setMarginTop(value.toInt());

            } else if (key == "MarginRight") {
                setMarginRight(value.toInt());

            } else if (key == "MarginBottom") {
                setMarginBottom(value.toInt());

            } else if (key == "InputStringPosX") {
                setInputStringPosX(value.toInt());

            } else if (key == "InputStringPosY") {
                setInputStringPosY(value.toInt());

            } else if (key == "OutputCandPosX") {
                setOutputCandPosX(value.toInt());

            } else if (key == "OutputCandPosY") {
                setOutputCandPosY(value.toInt());

            } else if (key == "BackArrowPosX") {
                setBackArrowPosX(value.toInt());

            } else if (key == "BackArrowPosY") {
                setBackArrowPosY(value.toInt());

            } else if (key == "ForwardArrowPosX") {
                setForwardArrowPosX(value.toInt());

            } else if (key == "ForwardArrowPosY") {
                setForwardArrowPosY(value.toInt());

            } else if (key == "BackArrow") {
                setBackArrowImg("file:/" + skinPath + value);

            } else if (key == "ForwardArrow") {
                setForwardArrowImg("file:/" + skinPath + value);

            }
        } else if (skinFontVertical) {
            if (key == "FontSize") {
                setFontSizeVertical(value.toInt());

            } else if (key == "CandFontSize") {
                setCandFontSizeVertical(value.toInt());

            } else if (key == "InputColor") {
                setInputColorVertical(value2color(value));

            } else if (key == "IndexColor") {
                setIndexColorVertical(value2color(value));

            } else if (key == "FirstCandColor") {
                setFirstCandColorVertical(value2color(value));

            } else if (key == "OtherColor") {
                setOtherColorVertical(value2color(value));

            }
        } else if (skinInputBarVertical) {
            if (key == "BackImg") {
                setInputBackImgVertical("file:/" + skinPath + value);

            } else if (key == "TipsImg") {
                setTipsImgVertical("file:/" + skinPath + value);

            } else if (key == "MarginLeft") {
                setMarginLeftVertical(value.toInt());

            } else if (key == "MarginTop") {
                setMarginTopVertical(value.toInt());

            } else if (key == "MarginRight") {
                setMarginRightVertical(value.toInt());

            } else if (key == "MarginBottom") {
                setMarginBottomVertical(value.toInt());

            } else if (key == "InputStringPosX") {
                setInputStringPosXVertical(value.toInt());

            } else if (key == "InputStringPosY") {
                setInputStringPosYVertical(value.toInt());

            } else if (key == "OutputCandPosX") {
                setOutputCandPosXVertical(value.toInt());

            } else if (key == "OutputCandPosY") {
                setOutputCandPosYVertical(value.toInt());

            } else if (key == "BackArrowPosX") {
                setBackArrowPosXVertical(value.toInt());

            } else if (key == "BackArrowPosY") {
                setBackArrowPosYVertical(value.toInt());

            } else if (key == "ForwardArrowPosX") {
                setForwardArrowPosXVertical(value.toInt());

            } else if (key == "ForwardArrowPosY") {
                setForwardArrowPosYVertical(value.toInt());

            } else if (key == "BackArrow") {
                setBackArrowImgVertical("file:/" + skinPath + value);

            } else if (key == "ForwardArrow") {
                setForwardArrowImgVertical("file:/" + skinPath + value);

            }
        }
    } while (!line.isNull());

    fcitxSkinConfFile.close();
    return true;
}

