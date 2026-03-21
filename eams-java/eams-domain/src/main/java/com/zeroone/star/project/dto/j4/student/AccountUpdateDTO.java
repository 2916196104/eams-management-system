package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

/**
 * 账号修改DTO
 */
@Data
@ApiModel(description = "账号修改DTO")
public class AccountUpdateDTO {
    @ApiModelProperty(value = "账号ID（必填）", example = "10001", required = true)
    @NotNull(message = "账号ID不能为空")
    private Long accountId;

    @ApiModelProperty(value = "账号名称", example = "admin_updated")
    private String accountName;

    @ApiModelProperty(value = "真实姓名", example = "管理员")
    private String realName;

    @ApiModelProperty(value = "手机号", example = "13800138001")
    private String phone;

    @ApiModelProperty(value = "账号状态（1启用/0禁用）", example = "1")
    private Integer status;

    @ApiModelProperty(value = "所属部门ID", example = "1001")
    private Long deptId;
}