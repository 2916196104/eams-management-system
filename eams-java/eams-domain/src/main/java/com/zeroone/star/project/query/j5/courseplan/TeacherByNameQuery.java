package com.zeroone.star.project.query.j5.courseplan;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/*
* 描述：教师名称查询对象
* */
@Data
public class TeacherByNameQuery extends PageQuery {

    @ApiModelProperty(value = "课程id，需要在用户选择完班级后，将班级对应的课程id传入该字段",required = false,example = "1")
    private Long courseId;

    @ApiModelProperty(value = "教师名称",required = false,example = "张三")
    private String teacherName;

    @ApiModelProperty(value = "人员类型 (1:上课老师, 2:助教，此字段在用户选择上课老师时传递1，选择助教时传递2)", required = false, example = "1")
    private Integer type;
}
