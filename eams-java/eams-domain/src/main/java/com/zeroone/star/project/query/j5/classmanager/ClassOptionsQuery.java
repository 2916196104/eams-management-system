package com.zeroone.star.project.query.j5.classmanager;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;

public class ClassOptionsQuery extends PageQuery {
    @ApiModelProperty(value = "班级名称", example = "班级名称")
    private String className;

}
