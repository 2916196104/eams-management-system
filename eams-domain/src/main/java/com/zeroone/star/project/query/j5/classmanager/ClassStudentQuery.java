package com.zeroone.star.project.query.j5.classmanager;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel(description = "学员分页查询参数")
public class ClassStudentQuery extends PageQuery {

    @ApiModelProperty(value = "学员姓名（模糊匹配）", example = "张")
    private String studentName;

    @ApiModelProperty(value = "性别 1男 2女", example = "1")
    private Integer gender;

}
