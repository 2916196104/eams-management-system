package com.zeroone.star.sys.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 描述：数据字典类型名称实体类
 * @author dabaocai
 */
@Data
@TableName("dict")
public class Dict {
    /**
     *数据id
     */
    @ApiModelProperty("主键ID")
    @TableId(type = IdType.AUTO)
    private  Integer id;
    /**
     * 数据名称
     */
    @ApiModelProperty("数据类型名称")
    private  String name;
    /**
     * 字典编码
     */
    @ApiModelProperty("字典编码")
    private String code;
    /**
     * 备注
     */
    @ApiModelProperty("备注")
    private  String remark;
    /**
     * 排序号
     */
    @ApiModelProperty("排序号")
    private  String sortNum;
}
