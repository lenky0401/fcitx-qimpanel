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

#ifndef __READ_WRITE_CFG_H__
#define __READ_WRITE_CFG_H__

/**
 * @brief get_fcitx_cfg_value：获取小企鹅输入配置值
 * @param cd_path_prefix：配置描述文件路径前缀
 * @param cd_file_name：配置描述文件名
 * @param c_path_prefix：配置文件路径前缀
 * @param c_file_name：配置文件名
 * @param groupName：具体配置项目所在组
 * @param optionName：具体配置项目名
 * @param ret_value：取得的配置值
 * @return：返回为true表示获取成功，反之获取失败
 */
bool get_fcitx_cfg_value(const char *cd_path_prefix, const char *cd_file_name,
    const char *c_path_prefix, const char *c_file_name, const char *groupName,  const char *optionName,
    void *ret_value);

/**
 * @brief set_fcitx_cfg_value：设置小企鹅输入配置值
 * @param cd_path_prefix：配置描述文件路径前缀
 * @param cd_file_name：配置描述文件名
 * @param c_path_prefix：配置文件路径前缀
 * @param c_file_name：配置文件名
 * @param groupName：具体配置项目所在组
 * @param optionName：具体配置项目名
 * @param ret_value：设置的配置值
 * @return：返回为true表示设置成功，反之获取失败
 */
bool set_fcitx_cfg_value(const char *cd_path_prefix, const char *cd_file_name,
    const char *c_path_prefix, const char *c_file_name, const char *groupName, const char *optionName,
    void *set_value);

void save_q_string_2_m_string(QString q_string, char **m_buf);

#endif // __READ_WRITE_CFG_H__
