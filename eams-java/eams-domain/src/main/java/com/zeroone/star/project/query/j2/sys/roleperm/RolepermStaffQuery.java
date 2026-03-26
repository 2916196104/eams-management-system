package com.zeroone.star.project.query.j2.sys.roleperm;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @author isme
 * @description   角色权限设置员工查询对象
 * @title com.zeroone.star.project.query.j2.sys
 * @date 2026/3/17
 */
@Data
public class RolepermStaffQuery extends PageQuery {
    @ApiModelProperty(value = "角色id", example = "1")
    private Integer roleId;

    @ApiModelProperty(hidden = true)
    private String name;
}
