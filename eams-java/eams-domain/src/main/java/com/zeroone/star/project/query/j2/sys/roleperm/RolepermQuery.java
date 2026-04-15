package com.zeroone.star.project.query.j2.sys.roleperm;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @author isme
 * @description   角色权限查询对象
 * @title com.zeroone.star.project.query.j2.sys
 * @date 2026/3/16
 */
@Data
public class RolepermQuery extends PageQuery {
    @ApiModelProperty(value = "角色id",example = "1")
    private int id;
    @ApiModelProperty(value = "角色名称",hidden = true)
    private String name;

    @ApiModelProperty(value = "角色编码",hidden = true)
    private String code;
}
