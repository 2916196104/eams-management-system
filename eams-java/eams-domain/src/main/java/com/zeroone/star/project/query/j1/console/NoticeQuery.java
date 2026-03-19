package com.zeroone.star.project.query.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel(value = "NoticeQuery", description = "公告查询条件")
public class NoticeQuery {

    @ApiModelProperty(value = "标题（模糊查询）")
    private String title;

    @ApiModelProperty(value = "当前页")
    private Integer pageNum = 1;

    @ApiModelProperty(value = "每页大小")
    private Integer pageSize = 30;
}
