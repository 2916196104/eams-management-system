package com.zeroone.star.project.query.j9.course;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Getter;
import lombok.Setter;

import javax.validation.constraints.NotNull;

/**
 * 关联课程分页查询条件
 * @author yangxiao
 */
@Getter
@Setter
@ApiModel("关联课程查询条件")
public class CourseLinkQuery extends PageQuery {

    @NotNull(message = "课程ID不能为空")
    @ApiModelProperty(value = "当前课程ID", required = true, example = "1")
    private Long courseId;

    @ApiModelProperty(value = "关联课程名（模糊搜索）", example = "Java")
    private String name;
}
