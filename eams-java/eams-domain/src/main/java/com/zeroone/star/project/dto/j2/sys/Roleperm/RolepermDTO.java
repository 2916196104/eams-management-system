package com.zeroone.star.project.dto.j2.sys.Roleperm;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @author isme
 * @description  角色权限数据传输对象
 * @title com.zeroone.star.project.dto.j2.sys
 * @date 2026/3/16
 */
@Data
public class RolepermDTO {
    @ApiModelProperty(value = "角色ID")
    private Long id;
    @ApiModelProperty(value = "角色名",example = "超级管理员")
    private String name;
    @ApiModelProperty(value = "编码",example = "superadmin")
    private String code;
}
