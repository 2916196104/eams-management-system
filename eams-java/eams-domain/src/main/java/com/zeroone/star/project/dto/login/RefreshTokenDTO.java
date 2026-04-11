package com.zeroone.star.project.dto.login;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;

@ApiModel("\u5237\u65b0\u4ee4\u724c\u8bf7\u6c42\u6570\u636e\u5bf9\u8c61")
@Data
public class RefreshTokenDTO {

    @ApiModelProperty(value = "\u8bbf\u95ee\u4ee4\u724c\uff0c\u517c\u5bb9\u65e7\u7ed3\u6784\u65f6\u53ef\u4f20", example = "mock-access-token")
    private String token;

    @ApiModelProperty(value = "\u5237\u65b0\u4ee4\u724c", example = "mock-refresh-token", required = true)
    @NotBlank(message = "\u5237\u65b0\u4ee4\u724c\u4e0d\u80fd\u4e3a\u7a7a")
    private String refreshToken;

    @ApiModelProperty(value = "\u7ec8\u7aef\u7c7b\u578b\uff0c\u53ef\u9009 manager / user\uff0c\u9ed8\u8ba4 manager", example = "manager")
    private String terminalType = "manager";
}
