package com.zeroone.star.project.dto.j8.stumanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Pattern;

/**
 * 学员家长账号修改DTO
 *
 * @author j26
 */
@Data
@ApiModel(value = "UserAccountDTO", description = "学员家长账号修改参数")
public class UserAccountDTO {

    @NotNull(message = "用户ID不能为空")
    @ApiModelProperty(value = "用户主键", example = "1", required = true)
    private Long id;

    @ApiModelProperty(value = "家长姓名", example = "张三")
    private String name;

    @NotBlank(message = "手机号不能为空")
    @Pattern(regexp = "^1[3-9]\\d{9}$", message = "手机号格式不正确")
    @ApiModelProperty(value = "手机号账号", example = "13800138000", required = true)
    private String mobile;

    @ApiModelProperty(value = "邮箱", example = "zhangsan@example.com")
    private String email;

    @ApiModelProperty(value = "账号状态：1-启用，0-禁用", example = "1")
    private Integer state;

    @ApiModelProperty(value = "备注", example = "VIP用户")
    private String remark;

    @ApiModelProperty(value = "所属学校ID", example = "1")
    private Long schoolId;
}
