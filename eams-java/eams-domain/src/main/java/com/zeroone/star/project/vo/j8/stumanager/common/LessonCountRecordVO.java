package com.zeroone.star.project.vo.j8.stumanager.common;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * Lesson count record view object.
 */
@Data
@ApiModel("Lesson count record view object")
public class LessonCountRecordVO {
    @ApiModelProperty(value = "Record ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "Student ID", example = "1")
    private Long studentId;

    @ApiModelProperty(value = "Student name", example = "Zhang San")
    private String studentName;

    @ApiModelProperty(value = "Course ID", example = "1001")
    private Long courseId;

    @ApiModelProperty(value = "Course name", example = "Math Advanced")
    private String courseName;

    @ApiModelProperty(value = "Lesson ID", example = "2001")
    private Long lessonId;

    @ApiModelProperty(value = "Lesson title", example = "Lesson 1")
    private String lessonTitle;

    @ApiModelProperty(value = "Changed lesson count", example = "-1")
    private Integer changeCount;

    @ApiModelProperty(value = "Remaining lesson count", example = "19")
    private Integer remainingCount;

    @ApiModelProperty(value = "Operator ID", example = "10")
    private Long staffId;

    @ApiModelProperty(value = "Operator name", example = "Li Teacher")
    private String staffName;

    @ApiModelProperty(value = "Stage", example = "1")
    private Integer stage;

    @ApiModelProperty(value = "Change time", example = "2026-03-15T10:00:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "Remark", example = "normal lesson deduction")
    private String remark;
}
