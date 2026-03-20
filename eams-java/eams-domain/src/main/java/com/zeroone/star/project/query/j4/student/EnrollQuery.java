package com.zeroone.star.project.query.j4.student;

import com.alibaba.excel.annotation.format.DateTimeFormat;
import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.*;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * EnrollmentQuery：学员ID、课程ID、报名时间区间
 */
@Getter
@Setter
@ToString
@ApiModel(value = "报名记录查询条件")
@EqualsAndHashCode(callSuper = true)
public class EnrollQuery extends PointsQuery {
    @ApiModelProperty(value = "学生姓名", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "课程名称", example = "美术")
    private String courseName;

    @ApiModelProperty(value = "报名开始时间", example = "2026-01-01")
    private String startTime;

    @ApiModelProperty(value = "报名结束时间", example = "2026-12-31")
    private String endTime;
}
