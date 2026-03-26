package com.zeroone.star.sys.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;

import io.swagger.annotations.ApiModelProperty;

import javax.validation.constraints.NotBlank;

import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;

/**
 * <p>
 * 描述：数据字典实体类
 * </p>
 * @author softmaple
 * @version 1.0.0
 */
@Setter
@Getter
@TableName("dict_item")
public class DictItem implements Serializable {
    /**
     * 序列化ID
     */
    private static final long serialVersionUID = 1L;

    /**
     * ID
     */
    @ApiModelProperty(value = "ID", example = "1")
    @TableId(type = IdType.AUTO)
    private Long id;
    /**
     * 数据字典ID
     */

    @ApiModelProperty(value = "数据字典ID", example = "1")
    private Long dictId;
    /**
     * 数据字典名称
     */
    @NotBlank(message = "数据字典名称不能为空")
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
