package com.zeroone.star.sys.controller;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.zeroone.star.project.dto.j2.sys.Sysparam.SettingDTO;
import com.zeroone.star.project.dto.j2.sys.Sysparam.SettingOptionDTO;
import com.zeroone.star.project.j2.sys.SysparamApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.sys.entity.sysparam.SettingDO;
import com.zeroone.star.sys.entity.sysparam.SettingOptionDO;
import com.zeroone.star.sys.service.sysparam.ISettingOptionService;
import com.zeroone.star.sys.service.sysparam.ISettingService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/j2-sys/sysparam")
@Api(tags = "系统参数")
public class SysparamController implements SysparamApis {

    @Resource
    private ISettingOptionService settingOptionService;
    @Resource
    private ISettingService settingService;


    @GetMapping("/list")
    @ApiOperation("获取设置列表")
    @Override
    public JsonVO<List<SettingDTO>> listSetting() {
        List<SettingDO> list = settingService.list();
        List<SettingDTO> dtoList = list.stream()
                                        .map(doObj -> {
                                            SettingDTO dto = new SettingDTO();
                                            BeanUtils.copyProperties(doObj,dto);
                                            return dto;
                                        })
                                        .collect(Collectors.toList());
        return JsonVO.success(dtoList);
    }

    @GetMapping("/{id}")
    @ApiOperation("获取设置详情")
    @Override
    public JsonVO<List<SettingOptionDTO>> listSettingOptionsById(@PathVariable Long id) {
        LambdaQueryWrapper<SettingOptionDO> queryWrapper = new LambdaQueryWrapper<>();
        queryWrapper.eq(SettingOptionDO::getSettingId,id);
        List<SettingOptionDO> list = settingOptionService.list(queryWrapper);
        List<SettingOptionDTO> dtoList = list.stream()
                                            .map(doObj -> {
                                                SettingOptionDTO dto = new SettingOptionDTO();
                                                BeanUtils.copyProperties(doObj,dto);
                                                return dto;
                                            })
                                            .collect(Collectors.toList());
        return JsonVO.success(dtoList);
    }

    @PutMapping("/update")
    @ApiOperation("保存设置")
    @Override
    public JsonVO<String> updateSettingOption(@RequestBody SettingOptionDTO settingOptionDTO) {
        SettingOptionDO settingOptionDO = new SettingOptionDO();
        BeanUtils.copyProperties(settingOptionDTO,settingOptionDO);
        boolean b = settingOptionService.updateById(settingOptionDO);
        return JsonVO.success("保存成功");
    }
}
