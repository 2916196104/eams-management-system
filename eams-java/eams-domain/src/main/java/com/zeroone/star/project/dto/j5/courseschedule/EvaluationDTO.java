package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.NonNull;

import javax.validation.constraints.Max;
import javax.validation.constraints.Min;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

@Data
public class EvaluationDTO {

//    @ApiModelProperty(value = "课次ID", required = true)
//    private Long lessonId;
//
//    @ApiModelProperty(value = "学生ID", required = true)
//    private Long studentId;

//    @ApiModelProperty(value = "老师ID（当前登录老师）", required = true)
//    private Long teacherId;

    @ApiModelProperty(value = "课程-学生表id",required = true)
    @NotNull(message = "课程学生关联ID不能为空")
    private Long id;


    @ApiModelProperty(value = "评分（1-5星）", required = true)
    @NotNull(message = "评分不能为空")
    @Min(1)
    @Max(5)
    private Integer score;

    @ApiModelProperty(value = "点评内容", required = true)
    @NotBlank(message = "评价内容不能为空")
    private String evaluation;

}
