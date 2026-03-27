package com.zeroone.star.sys.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
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
    @TableId(type = IdType.AUTO)
    private Long id;
    /**
     * 数据字典ID
     */
    private Long dictId;
    /**
     * 数据字典名称
     */
    private String name;
    /**
     * 数据字典说明
     */
    private String info;
    /**
     * 数据字典排序
     */
    private Integer sortNum;
}
