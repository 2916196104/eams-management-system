package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;

/**
 * <p>
 * 权限
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("sys_permission")
public class SysPermission implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Integer id;

    /**
     * 菜单名称
     */
    private String name;

    /**
     * 父类 id
     */
    private String parentId;

    /**
     * URL
     */
    private String url;

    /**
     * 权限编码
     */
    private String code;

    /**
     * 路径
     */
    private String path;

    /**
     * 是否启用 1 启用，0 禁用
     */
    private Integer enabled;

    /**
     * 分组
     */
    private String groupName;
}
