package com.zeroone.star.eamsj3class.entity;

import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 科目
 * </p>
 *
 * @author heavydrink
 * @since 2026-03-23
 */
@Getter
@Setter
public class Subject implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
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
    private Long creator;

    /**
     * 编辑者
     */
    private Long editor;

    /**
     * 新增时间
     */
    private LocalDateTime addTime;

    /**
     * 修改时间
     */
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
