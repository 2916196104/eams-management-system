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

    @ApiModelProperty(value = "创建人")
    private Long creator;
}
