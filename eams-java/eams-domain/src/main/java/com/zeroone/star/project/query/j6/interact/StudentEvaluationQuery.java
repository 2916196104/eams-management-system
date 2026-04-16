package com.zeroone.star.project.query.j6.interact;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;

/**
 * 教评学分页查询对象
 */
@Data
public class StudentEvaluationQuery extends PageQuery {
    @ApiModelProperty(value = "评价内容", example = "上课认真")
    private String evaluation;

    @ApiModelProperty(value = "课程id", example = "1768472940128731242")
    private Long lessonId;

    @ApiModelProperty(value = "老师id", example = "1768472939012456448")
    private Long teacherId;

    @ApiModelProperty(value = "学生id", example = "1768472940128731136")
    private Long studentId;


    @DateTimeFormat(pattern = "yyyy-MM-dd")
    @ApiModelProperty(value = "开始日期", example = "2024-06-01")
    private LocalDate startTime;

    @DateTimeFormat(pattern = "yyyy-MM-dd")
    @ApiModelProperty(value = "结束日期", example = "2024-06-30")
    private LocalDate endTime;
}
