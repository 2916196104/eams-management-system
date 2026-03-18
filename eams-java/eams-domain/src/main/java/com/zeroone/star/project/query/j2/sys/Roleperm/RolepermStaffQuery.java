package com.zeroone.star.project.query.j2.sys.Roleperm;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @author isme
 * @description   角色权限设置员工查询对象
 * @title com.zeroone.star.project.query.j2.sys
 * @date 2026/3/17
 */
@Data
public class RolepermStaffQuery {
    @ApiModelProperty(value = "员工姓名",example = "管理员")
    private String name;
}
