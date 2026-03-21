package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableName;
import com.baomidou.mybatisplus.annotation.IdType;
import java.time.LocalDateTime;
import com.baomidou.mybatisplus.annotation.TableId;
import java.io.Serializable;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.experimental.Accessors;

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
@TableName("user")
@ApiModel(value="User对象", description="家长端用户表")
public class User implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "用户主键")
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    @ApiModelProperty(value = "家长姓名")
    @TableField("name")
    private String name;

    @ApiModelProperty(value = "微信id")
    @TableField("wx_access_id")
    private Integer wxAccessId;

    @ApiModelProperty(value = "手机号账号")
    @TableField("mobile")
    private String mobile;

    @ApiModelProperty(value = "email")
    @TableField("email")
    private String email;

    @ApiModelProperty(value = "账号状态")
    @TableField("state")
    private Boolean state;

    @ApiModelProperty(value = "密码")
    @TableField("password")
    private String password;

    @ApiModelProperty(value = "登录次数")
    @TableField("login_times")
    private Integer loginTimes;

    @ApiModelProperty(value = "上次登录时间")
    @TableField("latest_login_time")
    private LocalDateTime latestLoginTime;

    @ApiModelProperty(value = "上次登录ip")
    @TableField("latest_login_ip")
    private String latestLoginIp;

    @ApiModelProperty(value = "加入时间")
    @TableField("add_time")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "备注")
    @TableField("remark")
    private String remark;

    @ApiModelProperty(value = "添加者")
    @TableField("creator")
    private Long creator;

    @ApiModelProperty(value = "所属学校id")
    @TableField("school_id")
    private Long schoolId;

    @ApiModelProperty(value = "创建者所属组织ID")
    @TableField("org_id")
    private Long orgId;


}
