package com.zeroone.star.project.dto.j1.org;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 *  组织界面里职位管理的数据权限类
 */
@ApiModel("数据权限实体类")
@Data
public class PositionDataPermissionDTO {

    @ApiModelProperty(value = "数据权限记录ID（新增不传，修改必传）", example = "1")
    private Long id;

    @ApiModelProperty(value = "数据表表名", required = true, example = "staff")
    private String entity_name;

    @ApiModelProperty(value = "数据权限范围类型（不填则表示按系统默认）", required = true, example = "1全部 2本校 3本部门 4自己")
    private Integer scope_type;


    @ApiModelProperty(value = "负责人字段（如果是修改数据,则要传,新增则不用）", example = "creator")
    private String owner_field;

    @ApiModelProperty(value = "数据所属组织字段名（不填则表示按系统默认）", example = "org_id")
    private String owner_org_field;

}
