package com.zeroone.star.project.vo.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalTime;

/**
 * Basic lesson detail view object.
 */
@Data
@ApiModel(value = "LessonDetailVO", description = "Lesson detail information")
public class LessonDetailVO {

    @ApiModelProperty(value = "Lesson id")
    private Long lessonId;

    @ApiModelProperty(value = "Lesson title")
    private String title;

    @ApiModelProperty(value = "Lesson state")
    private Integer state;

    @ApiModelProperty(value = "Lesson date")
    private LocalDate date;

    @ApiModelProperty(value = "Start time")
    private LocalTime startTime;

    @ApiModelProperty(value = "End time")
    private LocalTime endTime;
}
