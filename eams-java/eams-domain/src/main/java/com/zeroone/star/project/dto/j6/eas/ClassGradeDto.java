package com.zeroone.star.project.dto.j6.eas;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 年级表
 */
@Data
@ApiModel("年级表")
public class ClassGradeDto {
    /**
     * 年级id
     */
    @ApiModelProperty(value = "年级id,如果是修改数据必须传,新增不需要传",example = "2030583010845589505")
    private Long id;
    /**
     * 年级名称
     */
    @ApiModelProperty(value = "年级名称",example = "测试年级",required = true)
    private String name;
    /**
     * 入学年份
     */
    @ApiModelProperty(value = "入学年份",example = "2025",required = true)
    private Integer year;
    /**
     * 备注
     */
    @ApiModelProperty(value = "备注",example = "测试年级备注")
    private String remark;
    /**
     * 排序
     */
    @ApiModelProperty(value = "排序",example = "1")
    private Integer sortNum;
}
