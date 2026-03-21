package com.zeroone.star.project.query.j6.interact;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * <p>
 * 描述：学评教查询对象
 * </p>
 */
@Data
public class TeachEvaluationQuery{

    @ApiModelProperty(value = "老师id", example = "1768472939012456448")
    private Long teacherId;

    @ApiModelProperty(value = "学生id", example = "1768472940128731136")
    private Long studentId;

    @ApiModelProperty(value = "课程id",example = "1768472940128731242")
    private Long lessonId;

    @ApiModelProperty(value = "开始日期", example = "2024-06-01")
    private LocalDateTime startTime;

    @ApiModelProperty(value = "结束日期", example = "2024-06-30")
    private LocalDateTime endTime;

}