package com.zeroone.star.project.vo.j2.sys.Datadict;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：数据字典VO类
 * </p>
 * @author softmaple
 * @version 1.0.0
 */
@Data
@ApiModel(description = "数据字典VO类")
public class DatadictVO {
    /**
     * ID
     */
    @ApiModelProperty(value = "ID", example = "1")
    private Long id;
    /**
     * 数据字典ID
     */
    @ApiModelProperty(value = "数据字典ID", example = "1")
    private Long dictId;
    /**
     * 数据字典名称
     */
    @ApiModelProperty(value = "数据字典名称", example = "名称")
    private String name;
    /**
     * 数据字典说明
     */
    @ApiModelProperty(value = "数据字典说明", example = "说明")
    private String info;
    /**
     * 数据字典排序
     */
    @ApiModelProperty(value = "数据字典排序", example = "1")
    private Integer sortNum;

}
