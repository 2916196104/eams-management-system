package com.zeroone.star.project.query.j6.interact;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 描述：教评学查询对象
 * </p>
 */
@Data
public class StudentEvaluationQuery {
    @ApiModelProperty(value = "评价内容",example = "上课认真")
    private String evaluation;

    //todo 后面可能需要改为课程类
    @ApiModelProperty(value = "课程id", example = "1768472940128731242")
    private Long lessonId;

    //todo 后面可能需要改为教师类
    @ApiModelProperty(value = "老师id", example = "1768472939012456448")
    private Long teacherId;

    //todo 后面可能需要改为学生类
    @ApiModelProperty(value = "学生id", example = "1768472940128731136")
    private Long studentId;

    @ApiModelProperty(value = "开始日期", example = "2024-06-01")
    private LocalDateTime startTime;

    @ApiModelProperty(value = "结束日期", example = "2024-06-30")
    private LocalDateTime endTime;

}