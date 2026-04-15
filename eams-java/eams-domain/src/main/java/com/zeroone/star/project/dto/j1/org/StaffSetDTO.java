package com.zeroone.star.project.dto.j1.org;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

@Data
public class StaffSetDTO {
    @ApiModelProperty(value = "员工id", required = true, example = "[1]")
    private List<Long> staffIds;
    @ApiModelProperty(value = "角色id", required = true, example = "1")
    private Long roleId;
    @ApiModelProperty(value = "职位id", required = true, example = "1")
    private Long positionId;
}
