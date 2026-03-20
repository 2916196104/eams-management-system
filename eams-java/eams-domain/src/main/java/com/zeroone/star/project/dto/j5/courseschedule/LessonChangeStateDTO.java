package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

/**
 * Request DTO for lesson state changes.
 */
@Data
@ApiModel(value = "LessonChangeStateDTO", description = "Request parameters for changing lesson state")
public class LessonChangeStateDTO {

    /** Target lesson ids. */
    @ApiModelProperty(value = "Lesson id list", required = true)
    private List<Long> lessonIds;

    /** Target state value. */
    @ApiModelProperty(value = "Target state", required = true, notes = "0-stopped,1-underway,2-complete")
    private Integer targetState;

    /** Optional reason for state change. */
    @ApiModelProperty(value = "Change reason")
    private String reason;
}
