package com.zeroone.star.project.j8.sysmanager;

/**
 * 通知设置
 */
@Api(tags = "通知设置")
public interface NoticeSettingApis {
    @ApiOperation("获取通知设置")
    JsonVO<Void> getInformation();
    @ApiOperation("保存通知设置")
    JsonVO<Void> saveInformation();
}
