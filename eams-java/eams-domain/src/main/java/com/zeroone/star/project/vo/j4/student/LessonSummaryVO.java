package com.zeroone.star.project.vo.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel(description = "学员课时汇总VO")
public class LessonSummaryVO {
    @ApiModelProperty("学员ID")
    private String studentId;
    @ApiModelProperty("总课时")
    private Double totalHour;
    @ApiModelProperty("已用课时")
    private Double usedHour;
    @ApiModelProperty("剩余课时")
    private Double remainingHour;
}