
#include <QDebug>
#include <fcitx-config/fcitx-config.h>
#include "readcfg.h"

bool get_fcitx_cfg_value(const char *cd_path_prefix, const char *cd_file_name,
    const char *c_path_prefix, const char *c_file_name, const char *groupName,  const char *optionName,
    void *ret_value)
{
    FILE *c_fp;
    FILE *cd_fp;
    FcitxConfigFile *cfg;
    FcitxConfigFileDesc *cfg_desc;
    FcitxGenericConfig gc;

    if ((cd_fp = FcitxXDGGetFileWithPrefix(cd_path_prefix, cd_file_name, "r", NULL))
        == NULL)
    {
        qDebug() << QString("Open file(%0/%1) error.").arg(cd_path_prefix)
            .arg(cd_file_name);
        goto err;
    }

    if ((cfg_desc = FcitxConfigParseConfigFileDescFp(cd_fp)) == NULL) {
        qDebug() << "FcitxConfigParseConfigFileDescFp error.";
        goto err1;
    }

    if ((c_fp = FcitxXDGGetFileWithPrefix(c_path_prefix, c_file_name, "r", NULL))
        == NULL)
    {
        qDebug() << QString("Open file(%0/%1) error.").arg(c_path_prefix)
            .arg(c_file_name);
        goto err2;
    }

    if ((cfg = FcitxConfigParseConfigFileFp(c_fp, cfg_desc)) == NULL) {
        qDebug() << "FcitxConfigParseConfigFileFp error.";
        goto err3;
    }

    gc.configFile = cfg;
    FcitxConfigBindValue(cfg, groupName, optionName, ret_value, NULL, NULL);
    //把配置值绑定上来，即读取
    FcitxConfigBindSync(&gc);

    FcitxConfigFreeConfigFile(cfg);
    fclose(c_fp);
    FcitxConfigFreeConfigFileDesc(cfg_desc);
    fclose(cd_fp);

    return true;

err3:
    fclose(c_fp);
err2:
    FcitxConfigFreeConfigFileDesc(cfg_desc);
err1:
    fclose(cd_fp);
err:
    return false;
}
