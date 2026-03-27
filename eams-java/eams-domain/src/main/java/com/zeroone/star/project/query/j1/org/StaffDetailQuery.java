package com.zeroone.star.project.query.j1.org;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class StaffDetailQuery {

    @ApiModelProperty(value ="员工id",example="1")
    private  Integer id;
}
