package com.zeroone.star.j1.console.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.util.Date;

/**
 * <p>
 * 家长端用户表
 * </p>
 * @author hxb
 */
@Getter
@Setter
@TableName("user")
public class UserDO implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 用户主键
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

    /**
     * 家长姓名
     */
    private String name;

    /**
     * 微信id
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
    private Date latestLoginTime;

    /**
     * 上次登录ip
     */
    private String latestLoginIp;

    /**
     * 加入时间
     */
    private Date addTime;

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
