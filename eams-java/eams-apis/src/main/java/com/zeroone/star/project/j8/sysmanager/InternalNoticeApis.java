package com.zeroone.star.project.j8.sysmanager;

import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;

/**
 * 内部公告
 */
@Api(tags = "内部公告")

public interface InternalNoticeApis {
    @ApiOperation("删除内部公告")
    JsonVO deleteSysNotice();
}

