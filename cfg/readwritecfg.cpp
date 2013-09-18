/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  lenky gao    lenky0401@gmail.com
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

#include <QDebug>
#include <QString>
#include <fcitx-config/fcitx-config.h>
#include "readwritecfg.h"

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

bool set_fcitx_cfg_value(const char *cd_path_prefix, const char *cd_file_name,
    const char *c_path_prefix, const char *c_file_name, const char *groupName, const char *optionName,
    void *set_value)
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

    if ((c_fp = FcitxXDGGetFileWithPrefix(c_path_prefix, c_file_name, "r+", NULL))
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
    FcitxConfigBindValue(cfg, groupName, optionName, set_value, NULL, NULL);

    //把配置值绑定下去，即写入
    rewind(c_fp);
    if (FcitxConfigSaveConfigFileFp(c_fp, &gc, cfg_desc) == false) {
        qDebug() << "FcitxConfigSaveConfigFileFp error.";
        //Go Through
    }

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

void save_q_string_2_m_string(QString q_string, char **m_buf)
{
    int len;
    std::string tmp_str;
    char *m_buf_tmp;

    tmp_str = q_string.toStdString();
    len = tmp_str.length() + 1;

    if ((m_buf_tmp = (char *)malloc(len)) == NULL)
        return;

    memset(m_buf_tmp, 0, len);
    memcpy(m_buf_tmp, tmp_str.c_str(), len);

    if (*m_buf)
        free(*m_buf);

    *m_buf = m_buf_tmp;
}
