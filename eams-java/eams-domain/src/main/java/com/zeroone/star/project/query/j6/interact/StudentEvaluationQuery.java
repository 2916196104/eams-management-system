package com.zeroone.star.project.query.j6.interact;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：教评学查询对象
 * </p>
 */
@Data
public class StudentEvaluationQuery {
    @ApiModelProperty(value = "评价内容",example = "上课认真")
    private String evaluation;

    @ApiModelProperty(value = "课程id", example = "1768472940128731242")
    private Long lessonId;

    @ApiModelProperty(value = "老师id", example = "1768472939012456448")
    private Long teacherId;

    @ApiModelProperty(value = "学生id", example = "1768472940128731136")
    private Long studentId;

    @ApiModelProperty(value = "开始日期", example = "2024-06-01")
    private String startTime;

    @ApiModelProperty(value = "结束日期", example = "2024-06-30")
    private String endTime;

    @ApiModelProperty(value = "当前页数，默认为1", example = "1")
    private Long pageIndex = 1L;

    @ApiModelProperty(value = "每页条数，默认为30", example = "30")
    private Long pageSize = 30L;
}