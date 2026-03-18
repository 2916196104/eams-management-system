package com.zeroone.star.project.j2.sys;

import com.zeroone.star.project.dto.j2.sys.Sysparam.SettingDTO;
import com.zeroone.star.project.dto.j2.sys.Sysparam.SettingOptionDTO;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

/**
 * @author stfaly
 * 描述：系统参数接口声明
 */
public interface SysparamApis {

    /**
     * 获取设置列表
     * @return
     */
    JsonVO<List<SettingDTO>> listSetting();

    /**
     * 获取设置详情
     * @param id
     * @return
     */
    JsonVO<List<SettingOptionDTO>> listSettingOptionsById(Long id);

    /**
     * 保存设置
     * @param settingOptionDTO
     * @return
     */
    JsonVO<String> updateSettingOption(SettingOptionDTO settingOptionDTO);
}
