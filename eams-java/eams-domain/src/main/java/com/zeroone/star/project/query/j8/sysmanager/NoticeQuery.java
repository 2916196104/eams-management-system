package com.zeroone.star.project.query.j8.sysmanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.io.Serializable;

@Data
@ApiModel(value = "NoticeQuery", description = "公告查询参数")
public class NoticeQuery implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "搜索标题", example = "hellow")
    private String title;

    @ApiModelProperty(value = "创建者ID", example = "1")
    private Long creator;

    @ApiModelProperty(value = "当前页码", example = "1")
    private Integer pageNum = 1;

    @ApiModelProperty(value = "每页条数", example = "10")
    private Integer pageSize = 10;


}