package com.zeroone.star.project.vo.login;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

/**
 * <p>
 * 描述：当前登录用户展示对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 *
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("当前登录用户展示对象")
@Data
public class LoginVO {
    @ApiModelProperty(value = "用户编号", example = "1")
    private String id;

    @ApiModelProperty(value = "用户名", example = "admin")
    private String username;

    @ApiModelProperty(value = "是否启用，1启用，0禁用", example = "1")
    private Byte isEnabled;

    @ApiModelProperty(value = "角色列表", example = "[\"ADMIN\"]")
    private List<String> roles;
}
