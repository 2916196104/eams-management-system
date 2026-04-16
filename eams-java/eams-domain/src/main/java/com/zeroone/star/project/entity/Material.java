package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 物料表
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("material")
public class Material implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 所属学校
     */
    private Long schoolId;

    /**
     * 所属分类 ID
     */
    private Long categoryId;

    /**
     * 分类名
     */
    private String categoryName;

    /**
     * 物料名称
     */
    private String name;

    /**
     * 库存量
     */
    private Integer storage;

    /**
     * 物料说明
     */
    private String info;

    /**
     * 封面图
     */
    private String cover;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 添加时间
     */
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    private LocalDateTime editTime;

    /**
     * 删除标记
     */
    private Integer deleted;

    /**
     * 启用状态
     */
    private Integer state;

    /**
     * 创建者所属组织 ID
     */
    private Long orgId;
}
