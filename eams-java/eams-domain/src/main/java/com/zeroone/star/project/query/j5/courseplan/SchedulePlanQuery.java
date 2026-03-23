package com.zeroone.star.project.query.j5.courseplan;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/*
* 描述：排课计划查询对象
* */
@Data
public class SchedulePlanQuery extends PageQuery {
    @ApiModelProperty(value = "班级id",required = false,example = "1")
    private Integer classId;
    @ApiModelProperty(value = "课程名称",required = false,example = "日语")
    private String courseName;
//    @ApiModelProperty(value = "课堂类型",required = false,example = "1 大课  2 小班课 3 1v1")
//    private String lessonType;
}
