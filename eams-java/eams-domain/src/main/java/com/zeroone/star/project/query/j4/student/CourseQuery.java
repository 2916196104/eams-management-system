package com.zeroone.star.project.query.j4.student;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

//CourseQuery: 课程名称、类型、分页参数。
@Data
public class CourseQuery extends PageQuery {

    @ApiModelProperty(value = "课程名称", example = "Java课程", required = true)
    private String name;

    @ApiModelProperty(value = "课程类型(1:大班 2:小班课 3:1v1)", example = "1")
    private Integer type;

}
