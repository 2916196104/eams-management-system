package com.zeroone.star.project.dto.j6.eas;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 年级管理
 */
@Data
public class GradeManagerDto {
    /**
     * 年级id
     */
    @ApiModelProperty(value = "年级id")
    private Long id;

    /**
     * 年级名称
     */
    @ApiModelProperty(value = "年级名称")
    private String name;

    /**
     * 入学年份
     */
    @ApiModelProperty(value = "入学年份")
    private Integer year;

    /**
     * 备注
     */
    @ApiModelProperty(value = "备注")
    private String remark;

    /**
     * 排序
     */
    @ApiModelProperty(value = "排序")
    private Integer sort_num;
}
