package com.zeroone.star.project.query.j5.classmanager;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;

public class ClassPageQuery extends PageQuery {
    @ApiModelProperty(value = "班级名称（模糊匹配）", example = "三年二班")
    private String className;

    @ApiModelProperty(value = "课程名称（模糊匹配）", example = "数学")
    private String courseName;

    @ApiModelProperty(value = "班主任姓名（模糊匹配）", example = "张老师")
    private String teacherName;

    @ApiModelProperty(value = "教室名称（模糊匹配）", example = "A101")
    private String classroomName;

    @ApiModelProperty(value = "年级名称（模糊匹配）", example = "2026")
    private String gradeName;


}
