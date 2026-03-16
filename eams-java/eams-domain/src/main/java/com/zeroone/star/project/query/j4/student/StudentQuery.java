package com.zeroone.star.project.query.j4.student;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import io.swagger.annotations.Tag;
import lombok.Data;

//StudentQuery: 包含姓名、电话、状态（在线/意向/结业）、顾问ID、分页参数。
@Data
@ApiModel("学生相关信息查询")
public class StudentQuery extends PageQuery {
    @ApiModelProperty(value = "学员ID", example = "2008418408985583617")
    long StudentId;
}
