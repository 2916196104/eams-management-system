package com.zeroone.star.sys.controller;

import com.zeroone.star.project.dto.j2.sys.Sysparam.SettingDTO;
import com.zeroone.star.project.dto.j2.sys.Sysparam.SettingOptionDTO;
import com.zeroone.star.project.j2.sys.SysparamApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/sys/sysparam")
@Api(tags = "系统参数")
public class SysparamController implements SysparamApis {
    /**
     * 负责人：stfaly
     */
    @GetMapping()
    @ApiOperation("获取设置列表")
    @Override
    public JsonVO<List<SettingDTO>> listSetting() {
        return null;
    }

    @GetMapping("/{id}")
    @ApiOperation("获取设置详情")
    @Override
    public JsonVO<List<SettingOptionDTO>> listSettingOptionsById(@PathVariable Long id) {
        return null;
    }

    @PutMapping
    @ApiOperation("保存设置")
    @Override
    public JsonVO<String> updateSettingOption(@RequestBody SettingOptionDTO settingOptionDTO) {
        return null;
    }
}
