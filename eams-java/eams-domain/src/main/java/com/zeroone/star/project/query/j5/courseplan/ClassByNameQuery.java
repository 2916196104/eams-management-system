package com.zeroone.star.project.query.j5.courseplan;


import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/*
* 描述：根据班级姓名分页查询班级信息参数
* */
@Data
public class ClassByNameQuery extends PageQuery {
    @ApiModelProperty(value = "班级名称",required = false,example = "足球特长班")
    private String className;
}
