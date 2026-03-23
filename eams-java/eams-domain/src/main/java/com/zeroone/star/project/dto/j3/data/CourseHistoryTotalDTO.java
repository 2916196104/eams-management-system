package com.zeroone.star.project.dto.j3.data;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

@ApiModel("课程历史总销量模型")
@Data
public class CourseHistoryTotalDTO {
    @ApiModelProperty(value = "全部课程", example = "9.0")
    private Double countLessonTotal;

    @ApiModelProperty(value = "课程id", example = "1079")
    private Long courseId;

    @ApiModelProperty(value = "课程名字", example = "98测试")
    private String courseName;

    @ApiModelProperty(value = "课程全部收入", example = "1621196.40")
    private BigDecimal totalAmount;

    @ApiModelProperty(value = "全部报名数", example = "2")
    private Integer totalCount;

}
