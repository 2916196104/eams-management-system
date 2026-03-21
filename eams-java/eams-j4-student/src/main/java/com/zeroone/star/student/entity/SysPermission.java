package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import java.io.Serializable;
import java.util.Date;

/**
 * 系统权限表 DO
 * 对应数据库表：sys_permission
 */
@Data
@TableName("sys_permission")
public class SysPermission implements Serializable {
    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(type = IdType.AUTO)
    private Long id;

    /**
     * 权限名称
     */
    private String perm_name;

    /**
     * 权限编码（如：sys:user:list）
     */
    private String perm_code;

    /**
     * 权限类型（1-菜单，2-按钮，3-接口）
     */
    private Integer perm_type;

    /**
     * 父权限id（顶级权限为0）
     */
    private Long parent_id;

    /**
     * 路由地址（前端跳转路径）
     */
    private String router_path;

    /**
     * 组件路径（前端组件路径）
     */
    private String component_path;

    /**
     * 排序值
     */
    private Integer sort;

    /**
     * 权限状态（0-禁用，1-启用）
     */
    private Integer state;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 创建时间
     */
    private Date add_time;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 编辑时间
     */
    private Date edit_time;

    /**
     * 删除标记（0-未删除，1-已删除）
     */
    @TableLogic
    private Integer deleted;
}