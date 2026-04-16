package com.zeroone.star.project.vo.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * 新增课程结果 VO
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(description = "新增课程结果")
public class CourseAddVO {

    @ApiModelProperty(value = "是否新增成功", example = "true")
    private Boolean success;

    @ApiModelProperty(value = "成功新增后的课程ID", example = "1001")
    private Long courseId;
}