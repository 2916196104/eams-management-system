package com.zeroone.star.project.query.j5.schedule;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

/*
* 描述：教师名称查询对象
* */
@Data
public class TeacherByNameQuery extends PageQuery {
    @ApiModelProperty(value = "教师名称",required = false,example = "张三")
    private String teacherName;
}
