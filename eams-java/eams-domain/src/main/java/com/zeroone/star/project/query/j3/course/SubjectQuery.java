package com.zeroone.star.project.query.j3.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

/**
 * <p>
 * 描述：科目数据查询对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author fish
 * @version 1.0.0
 */

@Data
@ApiModel("科目数据查询对象")
public class SubjectQuery {
    @ApiModelProperty(value = "科目名称", example = "信息")
    private String name;
    @ApiModelProperty(value = "简介", example = " ")
    private String info;
    @ApiModelProperty(value = "排序值", example = "5")
    private Integer sortNum;
}
