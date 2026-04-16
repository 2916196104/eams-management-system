package com.zeroone.star.project.dto.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

import javax.validation.constraints.NotNull;

/**
 * 修改课程参数 DTO
 */
@Data
@EqualsAndHashCode(callSuper = true)
@ApiModel(description = "修改课程参数")
public class CourseUpdateDTO extends CourseAddDTO {

    @NotNull(message = "修改时课程ID不能为空")
    @ApiModelProperty(value = "课程ID（修改时必传）", required = true, example = "1001")
    private Long id;
}