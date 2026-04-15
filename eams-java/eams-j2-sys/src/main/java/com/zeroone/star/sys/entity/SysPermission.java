package com.zeroone.star.sys.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import java.io.Serializable;

import lombok.Data;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 权限
 * </p>
 *
 * @author Yaco
 * @since 2026-03-21
 */
@Getter
@Setter
@TableName("sys_permission")
@Data
public class SysPermission implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    private Long id;

    /**
     * 菜单名称
     */
    private String name;

    /**
     * 父类id
     */
    private String parentId;

    private String url;

    private String code;

    private String path;

    /**
     * 是否启用 1 启用，0 禁用
     */
    private Short enabled;

    /**
     * 分组
     */
    private String groupName;


}
