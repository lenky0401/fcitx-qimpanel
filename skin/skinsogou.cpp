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

#include "skinsogou.h"
#include "../main_model.h"

SkinSogou::SkinSogou() : SkinBase()
{

}

SkinSogou::~SkinSogou()
{

}

bool SkinSogou::loadSkin(const QString skinPath)
{
    init();
    QFile sogouSkinConfFile(skinPath + "skin.ini");

    if (!sogouSkinConfFile.exists())
        return false;

    if (!sogouSkinConfFile.open(QIODevice::ReadOnly))
        return false;


    QString line;
    QString key, value;

    /// parse ini file content
    bool general = false;
    bool display = false;
    bool scheme_h1 = false;
    bool scheme_v1 = false;
    bool statusbar = false;
    int h_pt, h_pb, h_pl, h_pr;
    int v_pt, v_pb, v_pl, v_pr;
    unsigned int pinyin_color, zhongwen_color, zhongwen_first_color, comphint_color;

    int fontPixelSize = 12;
    //        setCandFontSize(13);

    setTipsImg("file://usr/share/fcitx/skin/ubuntukylin-light1/tips.png");
    setBackArrowImg("file://usr/share/fcitx/skin/ubuntukylin-light2/prev.png");
    setForwardArrowImg("file://usr/share/fcitx/skin/ubuntukylin-light1/next.png");

    setAdjustWidth(10);
    setAdjustHeight(30);
    setHorizontalTileMode("Stretch");
    setVerticalTileMode("Stretch");
    setInputStringPosX(0);
    setInputStringPosY(0);
    setOutputCandPosX(0);
    setOutputCandPosY(0);

    QTextStream textStream(sogouSkinConfFile.readAll());
 
    do {

        line = textStream.readLine();

        if (line.isEmpty() || line.at(0) == '#')
            continue;

        if (line.at(0) == '[') {
            general = (line == "[General]");
            display = (line == "[Display]");
            scheme_h1 = (line == "[Scheme_H1]");
            scheme_v1 = (line == "[Scheme_V1]");
            statusbar = (line == "[StatusBar]");

            continue;
        }

        if (!line.contains('='))
            continue;

        key = line.split('=').at(0);
        value = line.split('=').at(1);

        if (value.isEmpty())
            continue;


        if (display) {
            if (key == "font_size")
                setFontSize(value.toInt());
            else if (key == "pinyin_color"){
                pinyin_color = value.toUInt(0, 0);
                setOtherColor(QColor(qRed(pinyin_color), qGreen(pinyin_color), qBlue(pinyin_color)));
            } 
            else if (key == "zhongwen_color"){
                zhongwen_color = value.toUInt(0, 0);
                setInputColor(QColor(qRed(zhongwen_color), qGreen(zhongwen_color), qBlue(zhongwen_color)));
            }
            else if (key == "zhongwen_first_color"){
                zhongwen_first_color = value.toUInt(0, 0);
                //setFirstCandColor(QColor(qRed(zhongwen_first_color), qGreen(zhongwen_first_color), qBlue(zhongwen_first_color)));
            }
            else if (key == "comphint_color"){
                comphint_color = value.toUInt(0, 0);
                setFirstCandColor(QColor(qRed(comphint_color), qGreen(comphint_color), qBlue(comphint_color)));
            }
        }else if (scheme_h1) {
            if (key == "pic" && MainModel::self()->isHorizontal()) {
                setInputBackImg("file:/" + skinPath + value);
            }
            else if (key == "pinyin_marge") {
                QStringList list = value.split(',');
                h_pt = list.at(0).trimmed().toInt();
                h_pb = list.at(1).trimmed().toInt();
                h_pl = list.at(2).trimmed().toInt();
                h_pr = list.at(3).trimmed().toInt();

                if (MainModel::self()->isHorizontal()){
                    setMarginTop(h_pt);
                    setMarginBottom(h_pb);
                    setMarginLeft(h_pl);
                    setMarginRight(h_pr);
                }
            }
        }else if (scheme_v1) {
            if (key == "pic" && !MainModel::self()->isHorizontal()) {
                setInputBackImg("file:/" + skinPath + value);
            }
            else if (key == "pinyin_marge") {
                QStringList list = value.split(',');
                v_pt = list.at(0).trimmed().toInt();
                v_pb = list.at(1).trimmed().toInt();
                v_pl = list.at(2).trimmed().toInt();
                v_pr = list.at(3).trimmed().toInt();

                if (!MainModel::self()->isHorizontal()){
                    setMarginTop(v_pt);
                    setMarginBottom(v_pb);
                    setMarginLeft(v_pl);
                    setMarginRight(v_pr);
                }
            }
        } else if (statusbar) {
            if (key == "pic") {
                //setTipsImg("file:/" + skinPath + value);
            }
        }


    } while (!line.isNull());

    sogouSkinConfFile.close();
    return true;
}


