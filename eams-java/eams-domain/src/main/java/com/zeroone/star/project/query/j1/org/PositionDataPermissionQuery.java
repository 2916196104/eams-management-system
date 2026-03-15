package com.zeroone.star.project.query.j1.org;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;

/**
 * 查询条件类
 */
public class PositionDataPermissionQuery extends PageQuery {

    @ApiModelProperty(value = "数据表表名",example = "staff")
    private String entity_name;

    @ApiModelProperty(value = "数据权限范围类型，不填则表示按系统默认",example = "1全部 2本校 3本部门 4自己")
    private Integer scope_type;


    @ApiModelProperty(value = "负责人字段,如果是修改数据,则要传,新增则不用",example = "creator")
    private String owner_field;

    @ApiModelProperty(value = "数据所属组织字段名，不填则表示按系统默认",example = "org_id")
    private String owner_org_field;

}
