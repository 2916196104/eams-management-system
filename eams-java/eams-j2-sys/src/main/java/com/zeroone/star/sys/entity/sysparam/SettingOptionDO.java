package com.zeroone.star.sys.entity.sysparam;

import com.baomidou.mybatisplus.annotation.TableName;
import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import java.io.Serializable;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.experimental.Accessors;

/**
 * <p>
 * 系统设置表
 * </p>
 *
 * @author stf
 * @since 2026-03-22
 */
@Data
@EqualsAndHashCode(callSuper = false)
@Accessors(chain = true)
@TableName("setting_option")
public class SettingOptionDO implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

    /**
     * 组id
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
