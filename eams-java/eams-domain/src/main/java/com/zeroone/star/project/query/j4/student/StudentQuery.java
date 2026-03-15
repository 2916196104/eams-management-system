package com.zeroone.star.project.query.j4.student;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

//StudentQuery: 包含姓名、电话、状态（在线/意向/结业）、顾问ID、分页参数。
@Data
public class StudentQuery extends PageQuery {

    @ApiModelProperty(value = "学生姓名")
    private String name;

    @ApiModelProperty(value = "阶段状态 0意向学员")
    private Integer stage;

}
