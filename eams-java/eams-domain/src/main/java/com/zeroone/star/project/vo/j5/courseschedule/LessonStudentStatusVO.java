package com.zeroone.star.project.vo.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * Student lesson status view object.
 */
@Data
@ApiModel(value = "LessonStudentStatusVO", description = "Student status info for a lesson")
public class LessonStudentStatusVO {

    @ApiModelProperty(value = "Lesson-student record id")
    private Long lessonStudentId;

    @ApiModelProperty(value = "Lesson id")
    private Long lessonId;

    @ApiModelProperty(value = "Student id")
    private Long studentId;

    @ApiModelProperty(value = "Sign state")
    private Integer signState;

    @ApiModelProperty(value = "Student name")
    private String studentName;
}
