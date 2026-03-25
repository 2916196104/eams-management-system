package com.zeroone.star.project.dto.j1.org;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

@Data
public class StaffSetDTO {
    @ApiModelProperty(value = "员工ID（新增时不传，编辑时传）", example = "1")
    private List<Long> ids;

    @ApiModelProperty(value = "员工职位", example = "1")
    private long positionId ;
}
