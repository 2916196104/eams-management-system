package com.zeroone.star.sysmanager.controller;

import com.zeroone.star.project.dto.j8.sysmanager.NoticeSettingDTO;
import com.zeroone.star.project.j8.sysmanager.NoticeSettingApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import com.zeroone.star.sysmanager.entity.SettingNotice;
import com.zeroone.star.sysmanager.service.ISettingNoticeService;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.BeanUtils;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;
import java.util.stream.Collectors;

/**
 * 通知设置
 */
@Api(tags = "通知设置")
@RestController
@RequestMapping("/j8-sys/notice-setting")
public class NoticeSettingController implements NoticeSettingApis {

    @Resource
    private ISettingNoticeService  noticeService;

    @GetMapping("/information")
    @ApiOperation("获取设置信息")
    @Override
    public JsonVO<List<NoticeSettingDTO>> getNoticeSetting() {
        List<SettingNotice> result = noticeService.list();
        List<NoticeSettingDTO> noticeSettingDTOS = result.stream()
                .map(entity->{
                    NoticeSettingDTO entityDTO = new NoticeSettingDTO();
                    BeanUtils.copyProperties(entity,entityDTO);//转换为前端接受的属性
                    return  entityDTO;
                }).collect(Collectors.toList());
        return JsonVO.success(noticeSettingDTOS);
    }

    @PostMapping("/save")
    @ApiOperation("保存设置信息")
    @Transactional(rollbackFor = Exception.class)
    @Override
    public JsonVO<Void> saveInformation(@RequestBody NoticeSettingDTO noticeSettingDTO) {

        SettingNotice settingNotice = new SettingNotice();
        // 使用 Spring BeanUtils 拷贝（字段名一致时最方便）
        BeanUtils.copyProperties(noticeSettingDTO, settingNotice);
        return noticeService.updateById(settingNotice) ? JsonVO.success(null) : JsonVO.fail(null);
    }
}
