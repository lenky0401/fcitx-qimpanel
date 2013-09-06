
#ifndef __SKIN_FCITX_H__
#define __SKIN_FCITX_H__

#include "skinbase.h"

class SkinFcitx : public SkinBase
{
public:
    SkinFcitx();
    virtual ~SkinFcitx();
    virtual bool loadSkin(const QString skinPath);

};

#endif // __SKIN_FCITX_H__
