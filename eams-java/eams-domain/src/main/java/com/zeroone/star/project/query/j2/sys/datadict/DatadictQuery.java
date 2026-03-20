package com.zeroone.star.project.query.j2.sys.datadict;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：数据字典查询对象
 * </p>
 * @author softmaple
 * @version 1.0.0
 */

@Data
@ApiModel(description = "数据字典查询对象")
public class DatadictQuery {
    /**
     * 数据字典ID
     */
    @ApiModelProperty(value = "数据字典ID", example = "1")
    private Long id;
    /**
     * 分页页码
     */
    @ApiModelProperty(value = "分页页码", example = "1")
    private Integer page;
    /**
     * 每页大小
     */
    @ApiModelProperty(value = "每页大小", example = "10")
    private Integer pageSize;
}
