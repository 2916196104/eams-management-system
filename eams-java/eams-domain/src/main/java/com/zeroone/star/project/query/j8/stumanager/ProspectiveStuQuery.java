package com.zeroone.star.project.query.j8.stumanager;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;
@Data
public class ProspectiveStuQuery {
    @ApiModelProperty(value = "意向学员的请求列表", example = "[1, 2, 3]", required = true)
    private List<Long> ids;
}
