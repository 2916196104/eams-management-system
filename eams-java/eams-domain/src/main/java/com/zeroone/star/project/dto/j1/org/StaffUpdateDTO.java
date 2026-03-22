package com.zeroone.star.project.dto.j1.org;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

@Data
@ApiModel(description = "员工状态更新DTO")
public class StaffUpdateDTO {
    @ApiModelProperty(value = "员工ID（新增时不传，编辑时传）", example = "1")
    private List<Long> ids;

    @ApiModelProperty(value = "员工状态", example = "1")
    private Integer status;
}
