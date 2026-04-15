package com.zeroone.star.project.dto.j5.edu;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.Date;

@Data
public class EvaluationDTO {


    @ApiModelProperty("主键id")
    private Long id;
    @ApiModelProperty("课次id")
    private Long lessonId;
    @ApiModelProperty("老师id")
    private Long teacherId;
    @ApiModelProperty("点评得分")
    private int score;
    @ApiModelProperty("评语")
    private String content;
    @ApiModelProperty("评价时间")
    private Date addTime;
    @ApiModelProperty("学生id")
    private Long studentId;

}
