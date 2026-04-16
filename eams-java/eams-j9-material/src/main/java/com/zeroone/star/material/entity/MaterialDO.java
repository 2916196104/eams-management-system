package com.zeroone.star.material.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 物料表
 * </p>
 *
 * @author fantast
 * @since 2026-03-16
 */
@Getter
@Setter
@TableName("material")
public class MaterialDO implements Serializable {

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
     * 所属分类ID
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
    @TableLogic
    private Boolean deleted;

    /**
     * 启用状态
     */
    private Boolean state;

    /**
     * 创建者所属组织ID
     */
    private Long orgId;
}
