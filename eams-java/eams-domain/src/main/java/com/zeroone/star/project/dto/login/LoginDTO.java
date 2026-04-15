package com.zeroone.star.project.dto.login;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.validation.constraints.NotBlank;

@ApiModel("\u767b\u5f55\u8bf7\u6c42\u6570\u636e\u5bf9\u8c61")
@Data
@NoArgsConstructor
public class LoginDTO {

    @ApiModelProperty(value = "\u7528\u6237\u540d", example = "admin", required = true)
    @NotBlank(message = "\u7528\u6237\u540d\u4e0d\u80fd\u4e3a\u7a7a")
    private String username;

    @ApiModelProperty(value = "\u5bc6\u7801", example = "123456", required = true)
    @NotBlank(message = "\u5bc6\u7801\u4e0d\u80fd\u4e3a\u7a7a")
    private String password;

    @ApiModelProperty(
            value = "\u9a8c\u8bc1\u7801\u6821\u9a8c\u7ed3\u679c\uff0c\u9a8c\u8bc1\u7801\u672a\u5f00\u542f\u65f6\u53ef\u4e3a\u7a7a",
            example = "captcha-check-result"
    )
    private String code;

    @ApiModelProperty(value = "\u7ec8\u7aef\u7c7b\u578b\uff0c\u53ef\u9009 manager / user\uff0c\u9ed8\u8ba4 manager", example = "manager")
    private String terminalType = "manager";

    public LoginDTO(String username, String password, String code) {
        this(username, password, code, "manager");
    }

    public LoginDTO(String username, String password, String code, String terminalType) {
        this.username = username;
        this.password = password;
        this.code = code;
        this.terminalType = terminalType;
    }
}
