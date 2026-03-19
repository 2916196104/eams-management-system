package com.zeroone.star.project.dto.j5.courseschedule;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

/**
 * Query DTO for lesson count logs.
 */
@Data
@EqualsAndHashCode(callSuper = true)
@ApiModel(value = "LessonCountLogQueryDTO", description = "Pagination query parameters for lesson count logs")
public class LessonCountLogQueryDTO extends PageQuery {

    /** Student id filter. */
    @ApiModelProperty(value = "Student id")
    private Long studentId;

    /** Course id filter. */
    @ApiModelProperty(value = "Course id")
    private Long courseId;

    /** Optional stage filter. */
    @ApiModelProperty(value = "Change stage")
    private Integer stage;
}
