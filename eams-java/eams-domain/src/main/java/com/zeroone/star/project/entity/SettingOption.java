package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;

/**
 * <p>
 * 系统设置表（选项）
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("setting_option")
public class SettingOption implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 组 id
     */
    private Long settingId;

    /**
     * 名称
     */
    private String name;

    /**
     * 码
     */
    private String code;

    /**
     * 值
     */
    private String value;

    /**
     * 值数据类型
     */
    private String valueType;

    /**
     * 说明
     */
    private String info;

    /**
     * 排序
     */
    private Integer sortNum;
}
