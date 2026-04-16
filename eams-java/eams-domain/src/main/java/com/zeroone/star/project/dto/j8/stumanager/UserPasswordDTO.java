package com.zeroone.star.project.dto.j8.stumanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;

/**
 * 修改密码DTO
 *
 * @author j26
 */
@Data
@ApiModel(value = "UserPasswordDTO", description = "修改密码参数")
public class UserPasswordDTO {

    @NotNull(message = "用户ID不能为空")
    @ApiModelProperty(value = "用户主键", example = "1", required = true)
    private Long id;

    @NotBlank(message = "原密码不能为空")
    @ApiModelProperty(value = "原密码", example = "oldPassword123", required = true)
    private String oldPassword;

    @NotBlank(message = "新密码不能为空")
    @Size(min = 6, max = 20, message = "密码长度需在6-20位之间")
    @ApiModelProperty(value = "新密码", example = "newPassword456", required = true)
    private String newPassword;

    @NotBlank(message = "确认密码不能为空")
    @ApiModelProperty(value = "确认新密码", example = "newPassword456", required = true)
    private String confirmPassword;
}
