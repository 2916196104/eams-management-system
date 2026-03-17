package com.zeroone.star.project.query.j1.orgmanager;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

/**
 * <p>
 * 描述：职位分页查询条件
 * </p>
 *
 * @author gzx
 * @version 1.0.0
 */
@Data
@EqualsAndHashCode(callSuper = true)
@ApiModel("职位分页查询条件")
public class WorkStationQueryCondition extends PageQuery {
    @ApiModelProperty(value = "职位名称，支持模糊搜索", example = "校长")
    private String name;
}
