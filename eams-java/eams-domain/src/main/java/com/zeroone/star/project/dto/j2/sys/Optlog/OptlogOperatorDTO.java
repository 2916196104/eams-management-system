package com.zeroone.star.project.dto.j2.sys.Optlog;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @author isme
 * @description  操作日志-操作人选择列表数据传输对象
 * @title com.zeroone.star.project.dto.j2.sys
 * @date 2026/3/22
 */
@Data
public class OptlogOperatorDTO {
    @ApiModelProperty(value = "员工id", example = "1")
    private Long id;

    @ApiModelProperty(value = "姓名", example = "管理员")
    private String name;

    @ApiModelProperty(value = "职位", example = "校长")
    private String positionName;
}

