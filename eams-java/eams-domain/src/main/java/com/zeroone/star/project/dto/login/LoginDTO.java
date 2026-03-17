package com.zeroone.star.project.dto.login;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.validation.constraints.NotBlank;

/**
 * <p>
 * 描述：登录请求数据对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 *
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("登录请求数据对象")
@Data
@AllArgsConstructor
@NoArgsConstructor
public class LoginDTO {
    /**
     * 用户名
     */
    @ApiModelProperty(value = "用户名", example = "admin", required = true)
    @NotBlank(message = "用户名不能为空")
    private String username;

    /**
     * 密码
     */
    @ApiModelProperty(value = "密码", example = "123456", required = true)
    @NotBlank(message = "密码不能为空")
    private String password;

    /**
     * 验证码
     */
    @ApiModelProperty(value = "验证码，未开启验证码时可为空", example = "A1B2")
    private String code;
}
