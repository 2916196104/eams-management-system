package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

@Data
@ApiModel("设置学员上课状态 DTO")
public class SetStudentsStatusDTO {

    @ApiModelProperty(value = "课次学员记录ID列表", required = true, example = "[1001, 1002]")
    private List<Long> lessonStudentIds;

    @ApiModelProperty(value = "目标状态 0-未签到 1-已签到 2-迟到 3-请假 4-旷课", required = true, example = "1")
    private String status;
}
