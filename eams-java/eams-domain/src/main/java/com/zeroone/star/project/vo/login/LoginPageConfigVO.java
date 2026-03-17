package com.zeroone.star.project.vo.login;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：登录页配置展示对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 *
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("登录页配置展示对象")
@Data
public class LoginPageConfigVO {
    @ApiModelProperty(value = "登录模式", example = "account-password")
    private String loginMode;

    @ApiModelProperty(value = "是否开启验证码", example = "true")
    private Boolean captchaEnabled;

    @ApiModelProperty(value = "验证码类型", example = "aj-captcha")
    private String captchaType;

    @ApiModelProperty(value = "验证码访问前缀", example = "/captcha")
    private String captchaPathPrefix;
}
