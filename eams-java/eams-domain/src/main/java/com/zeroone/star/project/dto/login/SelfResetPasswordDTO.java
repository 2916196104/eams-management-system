package com.zeroone.star.project.dto.login;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Pattern;

/**
 * Self-service password reset request.
 */
@ApiModel("\u81ea\u52a9\u91cd\u7f6e\u5bc6\u7801\u8bf7\u6c42\u5bf9\u8c61")
@Data
public class SelfResetPasswordDTO {

    @ApiModelProperty(value = "\u65b0\u5bc6\u7801", example = "abc12345", required = true)
    @NotBlank(message = "\u65b0\u5bc6\u7801\u4e0d\u80fd\u4e3a\u7a7a")
    @Pattern(
            regexp = "^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{8,}$",
            message = "\u65b0\u5bc6\u7801\u5fc5\u987b\u81f3\u5c118\u4f4d\u4e14\u540c\u65f6\u5305\u542b\u5b57\u6bcd\u548c\u6570\u5b57"
    )
    private String newPassword;
}
