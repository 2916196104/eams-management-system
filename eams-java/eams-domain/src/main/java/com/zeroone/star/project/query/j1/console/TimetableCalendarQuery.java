package com.zeroone.star.project.query.j1.console;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

/**
 * <p>
 * 描述：课表日历查询对象
 * </p>
 * @author hxb
 */
@Data
@ApiModel(value = "课表日历查询对象")
@EqualsAndHashCode(callSuper = true)
public class TimetableCalendarQuery extends PageQuery {

    @ApiModelProperty(value = "开始日期", example = "2026-03-01")
    private String startDate;

    @ApiModelProperty(value = "结束日期", example = "2026-03-31")
    private String endDate;

    @ApiModelProperty(value = "班级ID")
    private Long classId;

    @ApiModelProperty(value = "课程ID")
    private Long courseId;

    @ApiModelProperty(value = "教师ID")
    private Long teacherId;

    @ApiModelProperty(value = "学员ID")
    private Long studentId;
}
