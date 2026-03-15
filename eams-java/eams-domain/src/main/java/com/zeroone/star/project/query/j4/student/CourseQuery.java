package com.zeroone.star.project.query.j4.student;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

//CourseQuery: 课程名称、类型、分页参数。
@Data
public class CourseQuery extends PageQuery {

    @ApiModelProperty(value = "课程名称", example = "C语言")
    private String name;


}
