package com.zeroone.star.project.query.j5.edu;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/*
* 点评查询
*
* */
@Data
public class EvaluationQuery extends PageQuery {

    @ApiModelProperty(value = "学生姓名",required = false,example = "小明")
    private String name;


}
