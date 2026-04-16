package com.zeroone.star.project.query.j9.course;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("关联课程分页查询条件")
public class CourseLinkPageQuery extends PageQuery {
    @ApiModelProperty(value = "课程ID", example = "101",required = true)
    private Long courseId;

    @ApiModelProperty(value = "关联课程ID", example = "102")
    private Long linkedId;

    @ApiModelProperty(value = "关联课程名称(模糊查询)", example = "Java")
    private String linkedCourseName;

    @ApiModelProperty(value = "课程名称(模糊查询)", example = "Python")
    private String courseName;
}
