package com.zeroone.star.project.query.j1.org;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class StaffDetailQuery {
    @ApiModelProperty(value="员工姓名",example = "管理员")
    private String name;
    @ApiModelProperty(value="员工账号",example="admin")
    private String account;
    @ApiModelProperty(value = "在职状态",example ="1" )
    private Integer statue;
    @ApiModelProperty(value ="员工id",example="1")
    private  Integer id;
}
