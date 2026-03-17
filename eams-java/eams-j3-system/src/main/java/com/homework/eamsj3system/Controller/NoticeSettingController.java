package com.homework.eamsj3system.Controller;

import com.zeroone.star.project.dto.j3.noticsetting.NoticeSettingDTO;
import com.zeroone.star.project.dto.j3.noticsetting.PageDTO;
import com.zeroone.star.project.j3.notice.NoticeApis;
import com.zeroone.star.project.query.j3.noticesetting.NoticeSettingQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.system.NoticeSettingDetailVO;
import com.zeroone.star.project.vo.j3.system.NoticeSettingListVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController("j3/system")
@RequestMapping("/noticesetting")
@Api(tags = "通知设置")
public class NoticeSettingController implements NoticeApis{


    @GetMapping
    @ApiOperation("获取通知设置")
    @Override
    public JsonVO<PageDTO<NoticeSettingDTO>> queryNoticeSettingList(NoticeSettingQuery noticeSettingQuery) {
        return null;
    }

    @PostMapping
    @ApiOperation("保存通知设置")
    @Override
    public JsonVO<String> saveNoticeSetting( @RequestBody  NoticeSettingDTO noticeSettingDTO) {
        return null;
    }
}