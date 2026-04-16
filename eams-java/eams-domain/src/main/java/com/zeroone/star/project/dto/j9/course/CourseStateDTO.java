package com.zeroone.star.project.dto.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;

import javax.validation.constraints.NotNull;
import java.io.Serializable;

/**
 * 课程启用/禁用 DTO
 * @author yangxiao
 */
@Getter
@Setter
@ApiModel("课程启用/禁用参数")
public class CourseStateDTO implements Serializable {

    private static final long serialVersionUID = 1L;

    @NotNull(message = "课程ID不能为空")
    @ApiModelProperty(value = "课程ID", required = true, example = "1")
    private Long id;

    @NotNull(message = "目标状态不能为空")
    @ApiModelProperty(value = "目标状态（0禁用 1启用）", required = true, example = "1")
    private Integer state;
}
