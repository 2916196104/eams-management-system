package com.zeroone.star.project.j8.sysmanager;

/**
 * 内部公告
 */
@Api(tags = "内部公告")

public interface InternalNoticeApis {
    @ApiOperation("删除内部公告")
    JsonVO<PageDTO<noticeListDTO>> deleteSysNotice();
}

