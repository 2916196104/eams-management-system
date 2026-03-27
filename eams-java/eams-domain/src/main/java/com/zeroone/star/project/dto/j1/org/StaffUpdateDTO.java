package com.zeroone.star.project.dto.j1.org;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

@Data
@ApiModel("员工状态修改DTO")
public class StaffUpdateDTO {

    @ApiModelProperty(value = "员工ID集合", required = true)
    private List<Long> staffIds;

    @ApiModelProperty(value = "在职状态 0-离职 1-在职", required = true, allowableValues = "0,1")
    private Integer status;
}
