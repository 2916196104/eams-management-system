package com.zeroone.star.project.query.j1.console;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

@Data
@ApiModel(value = "TimetableCalendarQuery", description = "Schedule query")
public class TimetableCalendarQuery extends PageQuery {

    @ApiModelProperty(value = "Week start")
    private LocalDate weekStart;

    @ApiModelProperty(value = "Week end")
    private LocalDate weekEnd;

    @ApiModelProperty(value = "Class ID")
    private Long classId;

    @ApiModelProperty(value = "Course ID")
    private Long courseId;

    @ApiModelProperty(value = "Teacher ID")
    private Long teacherId;

    @ApiModelProperty(value = "Student ID")
    private Long studentId;
}
