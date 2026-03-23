package com.zeroone.star.project.query.j3.notice;

import io.swagger.annotations.ApiModelProperty;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

/**
 * <p>
 * 内部公告查询对象
 * </p>
 * @author 阿伟
 */
@Getter
@Setter
@ToString
public class NoticeQuery {

    @ApiModelProperty( value = "页码")
    private Integer pageNum = 1;

    @ApiModelProperty(value = "每页显示条数")
    private Integer pageSize = 10;

    @ApiModelProperty(value = "公告标题（模糊查询）")
    private String title;

    @ApiModelProperty(value = "公告类型（1-通知 2-公告 3-通告）")
    private Integer type;

    @ApiModelProperty(value = "发布人")
    private String publisher;

    @ApiModelProperty(value = "是否置顶（0-否 1-是）")
    private Integer isTop;

    @ApiModelProperty(value = "是否启用（0-禁用 1-启用）")
    private Integer isEnable;
}
