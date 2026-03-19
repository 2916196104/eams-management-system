package com.zeroone.star.project.j8.sysmanager;

import com.zeroone.star.project.dto.notice.noticeSettingDTO;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;

import java.util.List;

/**
 * 通知设置
 */
@Api(tags = "通知设置")
public interface NoticeSettingApis {
    @ApiOperation("获取通知设置")
    JsonVO<List<noticeSettingDTO>> getNoticeSetting() ;
    @ApiOperation("保存通知设置")
    JsonVO<Void> saveInformation(noticeSettingDTO noticeSettingDTO);
}
