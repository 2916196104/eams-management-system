package com.zeroone.star.project.vo.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

/**
 * 分页响应VO
 */
@Data
@ApiModel(description = "分页响应VO")
public class PageVO<T> {
    @ApiModelProperty(value = "总条数", example = "100")
    private Long total;

    @ApiModelProperty(value = "总页数", example = "10")
    private Integer pages;

    @ApiModelProperty(value = "当前页码", example = "1")
    private Integer pageNum;

    @ApiModelProperty(value = "每页条数", example = "10")
    private Integer pageSize;

    @ApiModelProperty(value = "数据列表")
    private List<T> list;
}