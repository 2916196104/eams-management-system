package com.zeroone.star.project.query.j8.stumanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 学员家长账号查询条件
 *
 * @author j26
 */
@Data
@ApiModel(value = "UserAccountQuery", description = "学员家长账号查询条件")
public class UserAccountQuery {

    @ApiModelProperty(value = "家长姓名", example = "张三")
    private String name;

    @ApiModelProperty(value = "手机号", example = "13800138000")
    private String mobile;

    @ApiModelProperty(value = "账号状态：1-启用，0-禁用", example = "1")
    private Integer state;

    @ApiModelProperty(value = "所属学校ID", example = "1")
    private Long schoolId;

    @ApiModelProperty(value = "所属组织ID", example = "1")
    private Long orgId;

    @ApiModelProperty(value = "当前页码", example = "1", required = true)
    private Integer pageNum = 1;

    @ApiModelProperty(value = "每页条数", example = "10", required = true)
    private Integer pageSize = 10;
}
