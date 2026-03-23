package com.zeroone.star.project.dto.j6.eas;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 年级名称dto
 */
@Data
@ApiModel("年级名称")
public class GradeNameDto {
    /**
     * 年级id
     */
    @ApiModelProperty(value = "年级id",example = "2030583010845589505")
    private Long id;
    /**
     * 年级名称
     */
    @ApiModelProperty(value = "年级名称",example = "测试年级")
    private String name;
}
