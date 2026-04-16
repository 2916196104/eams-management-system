package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * <p>
 * 家长端用户表
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("user")
public class User implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 用户主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 家长姓名
     */
    private String name;

    /**
     * 微信 id
     */
    private Long wxAccessId;

    /**
     * 手机号账号
     */
    private String mobile;

    /**
     * email
     */
    private String email;

    /**
     * 账号状态
     */
    private Integer state;

    /**
     * 密码
     */
    private String password;

    /**
     * 登录次数
     */
    private Integer loginTimes;

    /**
     * 上次登录时间
     */
    private LocalDateTime latestLoginTime;

    /**
     * 上次登录 ip
     */
    private String latestLoginIp;

    /**
     * 加入时间
     */
    private LocalDateTime addTime;

    /**
     * 备注
     */
    private String remark;

    /**
     * 添加者
     */
    private Long creator;

    /**
     * 所属学校 id
     */
    private Long schoolId;

    /**
     * 创建者所属组织 ID
     */
    private Long orgId;
}
