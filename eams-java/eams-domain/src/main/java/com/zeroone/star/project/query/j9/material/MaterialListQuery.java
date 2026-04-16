package com.zeroone.star.project.query.j9.material;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;

import javax.validation.constraints.NotNull;


@Data
@AllArgsConstructor
@NoArgsConstructor
@EqualsAndHashCode(callSuper = true)
@ApiModel("物料列表查询")
public class MaterialListQuery extends PageQuery {

    @ApiModelProperty(value = "物料名称模糊查询", example = "笔记本")
    private String name;

    @ApiModelProperty(value = "启用状态", example = "0")
    private Integer state;

}