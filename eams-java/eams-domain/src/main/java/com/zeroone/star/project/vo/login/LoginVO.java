package com.zeroone.star.project.vo.login;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

/**
 * Current logged-in user payload.
 */
@ApiModel("Current logged-in user")
@Data
public class LoginVO {
    @ApiModelProperty(value = "User id", example = "1")
    private String id;

    @ApiModelProperty(value = "Login account", example = "admin")
    private String username;

    @ApiModelProperty(value = "Display name", example = "Administrator")
    private String name;

    @ApiModelProperty(value = "Avatar URL", example = "https://example.com/avatar.png")
    private String avatar;

    @ApiModelProperty(value = "Mobile number", example = "13800138000")
    private String mobile;

    @ApiModelProperty(value = "Whether the account is enabled", example = "1")
    private Byte isEnabled;

    @ApiModelProperty(value = "Role codes", example = "[\"ADMIN\"]")
    private List<String> roles;

    @ApiModelProperty(value = "Permission codes", example = "[\"staff:add\",\"staff:update\"]")
    private List<String> permissions;
}
