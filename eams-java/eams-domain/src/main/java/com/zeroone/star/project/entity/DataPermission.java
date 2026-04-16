package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;

/**
 * <p>
 * 数据权限
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("data_permission")
public class DataPermission implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 岗位 id
     */
    private Long positionId;

    /**
     * 权限类型
     */
    private Integer scopeType;

    /**
     * 表名 (可重复)
     */
    private String entityName;

    /**
     * 数据所有人字段名
     */
    private String ownerField;

    /**
     * 备注
     */
    private String info;

    /**
     * 数据所有组织字段名
     */
    private String ownerOrgField;
}
