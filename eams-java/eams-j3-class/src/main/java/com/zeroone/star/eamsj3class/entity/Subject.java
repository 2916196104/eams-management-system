package com.zeroone.star.eamsj3class.entity;

import java.io.Serializable;
import java.time.LocalDateTime;

import com.baomidou.mybatisplus.annotation.FieldFill;
import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 科目
 * </p>
 *
 * @author fish
 * @since 2026-03-17
 */
@Getter
@Setter
public class Subject implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 科目
     */
    private String name;

    /**
     * 简介
     */
    private String info;

    /**
     * 创建人
     */
    @TableField(fill = FieldFill.INSERT)
    private Long creator;

    /**
     * 编辑者
     */
    @TableField(fill = FieldFill.UPDATE)
    private Long editor;

    /**
     * 新增时间
     */
    @TableField(fill = FieldFill.INSERT)
    private LocalDateTime addTime;

    /**
     * 修改时间
     */
    @TableField(fill = FieldFill.UPDATE)
    private LocalDateTime editTime;

    /**
     * 删除标记
     */
    private Integer deleted;

    /**
     * 排序值
     */
    private Integer sortNum;

    /**
     * 创建者所属组织ID
     */
    private Long orgId;


}
