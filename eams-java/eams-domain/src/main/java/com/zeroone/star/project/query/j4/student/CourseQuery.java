package com.zeroone.star.project.query.j4.student;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotNull;

//CourseQuery: 课程名称、类型、分页参数。
@Data
public class CourseQuery extends PageQuery {

    @ApiModelProperty(value = "班级id", example = "111",required = true)
    @NotNull(message = "班级id不能为空")
    private Long classId;

    @ApiModelProperty(value = "课程名称", example = "Java课程")
    private String name;

    @ApiModelProperty(value = "课程类型(1:大班 2:小班课 3:1v1)", example = "1")
    private Integer type;

}
