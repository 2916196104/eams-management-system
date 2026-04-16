package com.zeroone.star.project.dto.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.validation.constraints.NotEmpty;
import java.util.List;

/**
 * 批量删除课程参数 DTO
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(description = "批量删除课程参数")
public class CourseDeleteDTO {

    @NotEmpty(message = "至少选择一门要删除的课程")
    @ApiModelProperty(value = "课程ID列表", required = true, example = "[101, 102, 103]")
    private List<Long> ids;
}