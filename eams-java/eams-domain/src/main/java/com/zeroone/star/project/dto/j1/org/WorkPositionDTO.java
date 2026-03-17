package com.zeroone.star.project.dto.j1.org;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：职位数操传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Data
public class WorkPositionDTO {
    @ApiModelProperty(value = "职位id,如果是修改数据必须传，新增不传", example = "2008418408985583617")
    private Long id;
    @ApiModelProperty(value = "职位名称", example = "测试职位", required = true)
    private String name;
}
