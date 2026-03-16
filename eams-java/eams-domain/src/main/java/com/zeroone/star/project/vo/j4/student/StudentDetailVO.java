package com.zeroone.star.project.vo.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel(description = "学员课次详情VO")
public class StudentDetailVO {
    @ApiModelProperty("学员ID")
    private String studentId;
    @ApiModelProperty("学员姓名")
    private String studentName;
    @ApiModelProperty("课程总次数")
    private Integer courseTimes;
    @ApiModelProperty("剩余课程次数")
    private Integer remainingTimes;
}