package com.zeroone.star.project.dto.j1.org;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：员工重置密码数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author chichu
 * @version 1.0.0
 */
@Data
public class ResetPasswordDTO {
    @ApiModelProperty(value = "员工ID", example = "1", required = true)
    private Integer staffId;

    @ApiModelProperty(value = "新密码", example = "123456", required = true)
    private String newPassword;
}