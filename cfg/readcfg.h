
#ifndef __READ_CFG_H__
#define __READ_CFG_H__

/**
 * @brief FcitxCfgWizard::get_fcitx_cfg_value：获取小企鹅输入配置值
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

#endif // __READ_CFG_H__
