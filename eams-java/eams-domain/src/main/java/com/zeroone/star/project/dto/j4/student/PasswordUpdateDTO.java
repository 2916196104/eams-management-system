package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;

/**
 * 密码修改DTO
 */
@Data
@ApiModel(description = "密码修改DTO")
public class PasswordUpdateDTO {
    @ApiModelProperty(value = "账号ID（必填）", example = "10001", required = true)
    @NotBlank(message = "账号ID不能为空")
    private String accountId;

    @ApiModelProperty(value = "旧密码（必填）", example = "123456", required = true)
    @NotBlank(message = "旧密码不能为空")
    private String oldPassword;

    @ApiModelProperty(value = "新密码（必填，8-16位字母数字组合）", example = "Admin@123456", required = true)
    @NotBlank(message = "新密码不能为空")
    private String newPassword;

    @ApiModelProperty(value = "确认新密码（必填）", example = "Admin@123456", required = true)
    @NotBlank(message = "确认新密码不能为空")
    private String confirmPassword;
}