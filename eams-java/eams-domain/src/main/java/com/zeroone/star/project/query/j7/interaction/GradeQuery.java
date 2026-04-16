package com.zeroone.star.project.query.j7.interaction;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

//成绩单查询对象
@Data
public class GradeQuery extends PageQuery {
@ApiModelProperty(value = "考核项")
    private String title;
}
