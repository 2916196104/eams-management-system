package com.zeroone.star.project.query.j4.student;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;

/**
 * <p>
 * 描述：班级查询对象
 */
@Data
public class ClassQuery extends PageQuery {

    @ApiModelProperty(value = "班级名称 (模糊查询)", example = "Java就业班")
    private String name;

    @ApiModelProperty(value = "课程ID", example = "1001")
    private Long courseId;

    @ApiModelProperty(value = "班级负责人/教师ID", example = "2001")
    private Long teacherId;

    @ApiModelProperty(value = "学校ID", example = "500")
    private Long schoolId;

    @ApiModelProperty(value = "组织ID", example = "10")
    private Long orgId;

    @ApiModelProperty(value = "年级ID", example = "2023")
    private Integer gradeId;

    @ApiModelProperty(value = "是否完结 (0:未完结 1:完结)", example = "0")
    private Integer beOver;

    @ApiModelProperty(value = "计划开班开始日期", example = "2026-03-01")
    @JsonFormat(pattern = "yyyy-MM-dd", timezone = "GMT+8")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;

    @ApiModelProperty(value = "计划开班结束日期", example = "2026-06-30")
    @JsonFormat(pattern = "yyyy-MM-dd", timezone = "GMT+8")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate endDate;
}