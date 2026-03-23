package com.zeroone.star.project.query.j8.StuSignCourseQuery;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("课程查询条件")
public class CourseQuery extends PageQuery {
    @ApiModelProperty("课程名称")
    private String courseName;
}
