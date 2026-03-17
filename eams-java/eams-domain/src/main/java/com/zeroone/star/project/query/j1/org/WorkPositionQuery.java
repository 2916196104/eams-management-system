package com.zeroone.star.project.query.j1.org;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：职位查询对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Data
public class WorkPositionQuery extends PageQuery {
    @ApiModelProperty(value = "职位名称", example = "职位名称")
    private String name;
}
