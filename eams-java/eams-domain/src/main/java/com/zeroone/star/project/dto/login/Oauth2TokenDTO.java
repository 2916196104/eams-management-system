package com.zeroone.star.project.dto.login;

import com.fasterxml.jackson.annotation.JsonIgnore;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * <p>
 * 描述：登录认证响应数据对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 *
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("登录认证响应数据对象")
@Data
@NoArgsConstructor
@AllArgsConstructor
public class Oauth2TokenDTO {
    /**
     * 访问令牌
     */
    @ApiModelProperty(value = "访问令牌", example = "mock-access-token")
    private String token;

    /**
     * 刷新令牌
     */
    @ApiModelProperty(value = "刷新令牌", example = "mock-refresh-token")
    private String refreshToken;

    /**
     * Token 前缀
     */
    @ApiModelProperty(value = "Token前缀", example = "Bearer ")
    private String tokenHead;

    /**
     * 有效时间
     */
    @ApiModelProperty(value = "有效时间，单位秒", example = "3600")
    private Integer expiresIn;

    /**
     * 客户端ID
     */
    @JsonIgnore
    @ApiModelProperty(value = "客户端ID", example = "eams-manager", hidden = true)
    private String clientId;
}
