package com.zeroone.star.project.dto.j2.sys.Roleperm;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @author isme
 * @description  角色权限设置员工数据传输对象
 * @title com.zeroone.star.project.dto.j2.sys
 * @date 2026/3/17
 */
@Data
public class RolepermStaffDTO {
    @ApiModelProperty(value = "角色id", example = "1")
    private Integer roleId;

    @ApiModelProperty(value = "员工id",example = "1")
    private int id;
    @ApiModelProperty(value = "员工姓名",example = "管理员")
    private String name;
    @ApiModelProperty(value = "手机号",example = "")
    private String mobile;
}
