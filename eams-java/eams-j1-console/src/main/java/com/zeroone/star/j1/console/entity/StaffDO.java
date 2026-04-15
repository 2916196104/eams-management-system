package com.zeroone.star.j1.console.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.math.BigDecimal;
import java.util.Date;

/**
 * <p>
 * 教师员工表
 * </p>
 * @author hxb
 */
@Getter
@Setter
@TableName("staff")
public class StaffDO implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

    /**
     * 姓名
     */
    private String name;

    /**
     * 手机号
     */
    private String mobile;

    /**
     * 微信登录id
     */
    private Long wxAccessId;

    /**
     * EMAIL
     */
    private String email;

    /**
     * 生日
     */
    private Date birthday;

    /**
     * 性别
     */
    private Integer gender;

    /**
     * 身份证
     */
    private String idCard;

    /**
     * 毕业学校
     */
    private String school;

    /**
     * 学历
     */
    private Integer degree;

    /**
     * 备注
     */
    private String remark;

    /**
     * 在职状态
     */
    private Integer state;

    /**
     * 是否是管理者
     */
    private Integer isManager;

    /**
     * 头像
     */
    private String headImg;

    /**
     * 入职日期
     */
    private Date hireDate;

    /**
     * 离职日期
     */
    private Date fireDate;

    /**
     * 介绍
     */
    private String intro;

    /**
     * 创建时间
     */
    private Date addTime;

    /**
     * 编辑时间
     */
    private Date editTime;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 是否删除
     */
    private Integer deleted;

    /**
     * 密码
     */
    private String password;

    /**
     * 课时费
     */
    private BigDecimal classFee;

    /**
     * 助教费
     */
    private BigDecimal assistantFee;

    /**
     * STAFF所属组织ID
     */
    private Long orgId;

    /**
     * 是否内部人员
     */
    private Integer isInner;
}
