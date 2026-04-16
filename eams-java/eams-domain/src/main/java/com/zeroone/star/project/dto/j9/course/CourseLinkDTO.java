package com.zeroone.star.project.dto.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

@Data
@ApiModel("关联课程数据")
public class CourseLinkDTO {
    @ApiModelProperty(value = "课程名称", example = "钢琴入门课")
    private String name;

    @ApiModelProperty(value = "科目", example = "钢琴")
    private String subjectName;

    @ApiModelProperty(value = "价格", example = "1000")
    private BigDecimal price;

    @ApiModelProperty(value = "单位", example = "次")
    private String unitName;

    @ApiModelProperty(value = "班型", example = "小班课")
    private String lessonTypeName;

}
