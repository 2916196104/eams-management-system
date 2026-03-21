package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import java.io.Serializable;
import java.util.Date;

/**
 * 系统角色表 DO
 * 对应数据库表：sys_role
 */
@Data
@TableName("sys_role")
public class SysRole implements Serializable {
    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(type = IdType.AUTO)
    private Long id;

    /**
     * 角色名称
     */
    private String role_name;

    /**
     * 角色编码（唯一）
     */
    private String role_code;

    /**
     * 角色描述
     */
    private String role_desc;

    /**
     * 角色状态（0-禁用，1-启用）
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

    /**
     * 所属组织ID（多租户/多校区场景）
     */
    private Long org_id;
}