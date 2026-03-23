package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModelProperty;

public class EvaluationDTO {

    @ApiModelProperty(value = "课次ID", required = true)
    private Long lessonId;

    @ApiModelProperty(value = "学生ID", required = true)
    private Long studentId;

    @ApiModelProperty(value = "老师ID（当前登录老师）", required = true)
    private Long teacherId;

    @ApiModelProperty(value = "评分（1-5星）", required = true)
    private Integer score;

    @ApiModelProperty(value = "点评内容", required = true)
    private String content;

}
