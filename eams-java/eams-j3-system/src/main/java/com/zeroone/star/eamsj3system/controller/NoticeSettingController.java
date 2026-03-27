package com.zeroone.star.eamsj3system.controller;

import com.zeroone.star.eamsj3system.service.ISettingNoticeService;
import com.zeroone.star.project.dto.j3.notice.NoticeSettingDTO;
import com.zeroone.star.project.j3.notice.NoticeApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController("j3/system")
@RequestMapping("/noticesetting")
@Api(tags = "通知设置")
public class NoticeSettingController implements NoticeApis{

    @Autowired
    private ISettingNoticeService settingNoticeService;

    @GetMapping("/query-settinglist")
    @ApiOperation("获取通知设置")
    @Override
    public JsonVO<NoticeSettingDTO> queryNoticeSettingList() {
        return settingNoticeService.getNoticeSettingList();
    }

    @PostMapping("/savesetting")
    @ApiOperation("保存通知设置")
    @Override
    public JsonVO<NoticeSettingDTO> saveNoticeSetting( @RequestBody  NoticeSettingDTO noticeSettingDTO) {
        return settingNoticeService.saveNoticeSetting(noticeSettingDTO);
    }
}