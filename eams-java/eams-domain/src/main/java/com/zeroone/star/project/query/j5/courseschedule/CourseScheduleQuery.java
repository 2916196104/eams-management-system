package com.zeroone.star.project.query.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDate;

/**
 * 排课计划查询条件
 *
 * @author j5-courseschedule
 * @since 2026-03-17
 */
@Data
@ApiModel(description = "排课计划查询条件")
public class CourseScheduleQuery implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "班级ID", example = "2001")
    private Long classId;

    @ApiModelProperty(value = "课程ID", example = "3001")
    private Long courseId;

    @ApiModelProperty(value = "教师ID", example = "101")
    private Long teacherId;

    @ApiModelProperty(value = "是否生成课表：0-未生成 1-已生成", example = "0")
    private Integer state;

    @ApiModelProperty(value = "开始日期（范围查询起始）", example = "2026-03-01")
    private LocalDate startDateBegin;

    @ApiModelProperty(value = "开始日期（范围查询结束）", example = "2026-06-30")
    private LocalDate startDateEnd;

    @ApiModelProperty(value = "组织ID", example = "100")
    private Long orgId;

    @ApiModelProperty(value = "页码", example = "1")
    private Integer pageNum = 1;

    @ApiModelProperty(value = "每页数量", example = "10")
    private Integer pageSize = 10;
}
