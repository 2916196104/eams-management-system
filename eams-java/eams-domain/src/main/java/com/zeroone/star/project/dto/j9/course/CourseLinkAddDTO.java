package com.zeroone.star.project.dto.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;

import javax.validation.constraints.NotEmpty;
import javax.validation.constraints.NotNull;
import java.io.Serializable;
import java.util.List;

/**
 * 添加关联课程 DTO（支持多选）
 * @author yangxiao
 */
@Getter
@Setter
@ApiModel("添加关联课程参数")
public class CourseLinkAddDTO implements Serializable {

    private static final long serialVersionUID = 1L;

    @NotNull(message = "课程ID不能为空")
    @ApiModelProperty(value = "当前课程ID", required = true, example = "1")
    private Long courseId;

    @NotEmpty(message = "关联课程ID列表不能为空")
    @ApiModelProperty(value = "要关联的课程ID列表", required = true, example = "[2, 3, 5]")
    private List<Long> linkedIds;
}
