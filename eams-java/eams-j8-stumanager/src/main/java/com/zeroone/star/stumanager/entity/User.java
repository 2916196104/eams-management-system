package com.zeroone.star.stumanager.entity;

import java.io.Serializable;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 家长端用户表
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Getter
@Setter
public class User implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 用户主键
     */
    private Long id;

    /**
     * 家长姓名
     */
    private String name;

    /**
     * 微信id
     */
    private Integer wxAccessId;

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
    private Boolean state;

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
     * 上次登录ip
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
     * 所属学校id
     */
    private Long schoolId;

    /**
     * 创建者所属组织ID
     */
    private Long orgId;


}
