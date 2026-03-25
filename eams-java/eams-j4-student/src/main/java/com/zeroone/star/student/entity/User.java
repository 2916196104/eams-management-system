package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableName;
import com.baomidou.mybatisplus.annotation.IdType;
import java.io.Serializable;
import java.time.LocalDateTime;
import com.baomidou.mybatisplus.annotation.TableId;
import io.swagger.annotations.ApiModel;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.experimental.Accessors;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

/**
 * <p>
 * 家长端用户表
 * </p>
 *
 * @author zrt
 * @since 2026-03-16
 */
@Data
@EqualsAndHashCode(callSuper = false)
@Accessors(chain = true)
@Getter
@Setter
@TableName("user")
@ApiModel(value="User对象", description="家长端用户表")
public class User implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(type = IdType.AUTO)
    private Long id;

    @TableField("name")
    private String name;

    @TableField("wx_access_id")
    private Integer wxAccessId;

    @TableField("mobile")
    private String mobile;

    @TableField("email")
    private String email;

    @TableField("state")
    private Boolean state;

    @TableField("password")
    private String password;

    @TableField("login_times")
    private Integer loginTimes;

    @TableField("latest_login_time")
    private LocalDateTime latestLoginTime;

    @TableField("latest_login_ip")
    private String latestLoginIp;

    @TableField("add_time")
    private LocalDateTime addTime;

    @TableField("remark")
    private String remark;

    @TableField("creator")
    private Long creator;

    @TableField("school_id")
    private Long schoolId;

    @TableField("org_id")
    private Long orgId;
}
