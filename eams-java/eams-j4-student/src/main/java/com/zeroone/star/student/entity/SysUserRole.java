package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import java.io.Serializable;
import java.util.Date;

/**
 * 系统用户角色关联表 DO
 * 对应数据库表：sys_user_role
 */
@Data
@TableName("sys_user_role")
public class SysUserRole implements Serializable {
    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(type = IdType.AUTO)
    private Long id;

    /**
     * 用户id（关联user/staff表，根据业务场景适配）
     */
    private Long user_id;

    /**
     * 角色id
     */
    private Long role_id;

    /**
     * 关联状态（0-失效，1-生效）
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