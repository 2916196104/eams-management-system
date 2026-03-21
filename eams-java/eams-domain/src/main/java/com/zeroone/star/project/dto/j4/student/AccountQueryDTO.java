package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 账号列表查询DTO（条件+分页）
 */
@Data
@ApiModel(description = "账号列表查询DTO")
public class AccountQueryDTO {
    @ApiModelProperty(value = "账号名称（模糊查询）", example = "admin")
    private String accountName;

    @ApiModelProperty(value = "账号状态（1启用/0禁用）", example = "1")
    private Integer status;

    @ApiModelProperty(value = "所属部门ID", example = "1001")
    private Long deptId;

    @ApiModelProperty(value = "页码（默认1）", example = "1", required = true)
    private Integer pageNum = 1;

    @ApiModelProperty(value = "每页条数（默认10）", example = "10", required = true)
    private Integer pageSize = 10;
}