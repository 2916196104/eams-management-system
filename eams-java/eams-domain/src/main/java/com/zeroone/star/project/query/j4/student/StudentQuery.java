package com.zeroone.star.project.query.j4.student;

import io.swagger.annotations.ApiModelProperty;
import io.swagger.annotations.Tag;
import lombok.Data;

//StudentQuery: 包含姓名、电话、状态（在线/意向/结业）、顾问ID、分页参数。
@Data
public class StudentQuery {
    @ApiModelProperty(value = "学员ID", example = "2008418408985583617")
    long StudentId;
}
