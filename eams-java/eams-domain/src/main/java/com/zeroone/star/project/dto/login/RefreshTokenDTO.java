package com.zeroone.star.project.dto.login;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;

/**
 * <p>
 * 描述：刷新令牌请求数据对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 *
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("刷新令牌请求数据对象")
@Data
public class RefreshTokenDTO {
    /**
     * 访问令牌
     */
    @ApiModelProperty(value = "访问令牌，兼容旧结构时可传", example = "mock-access-token")
    private String token;

    /**
     * 刷新令牌
     */
    @ApiModelProperty(value = "刷新令牌", example = "mock-refresh-token", required = true)
    @NotBlank(message = "刷新令牌不能为空")
    private String refreshToken;
}
