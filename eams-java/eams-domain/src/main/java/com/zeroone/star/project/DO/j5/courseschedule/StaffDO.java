package com.zeroone.star.project.DO.j5.courseschedule;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import com.baomidou.mybatisplus.annotation.TableLogic;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * @author silvan
 * @description 教师员工表
 */
@TableName("staff")
@Data
public class StaffDO {

    /**
     * 主键ID
     */
    @TableId(type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 姓名
     */
    @TableField("name")
    private String name;

    /**
     * 手机号
     */
    @TableField("mobile")
    private String mobile;

    /**
     * 微信登录id
     */
    @TableField("wx_access_id")
    private Long wxAccessId;

    /**
     * EMAIL
     */
    @TableField("email")
    private String email;

    /**
     * 生日
     */
    @TableField("birthday")
    private LocalDate birthday;

    /**
     * 性别
     */
    @TableField("gender")
    private Byte gender;

    /**
     * 身份证
     */
    @TableField("id_card")
    private String idCard;

    /**
     * 毕业学校
     */
    @TableField("school")
    private String school;

    /**
     * 学历
     */
    @TableField("degree")
    private Byte degree;

    /**
     * 备注
     */
    @TableField("remark")
    private String remark;

    /**
     * 在职状态
     */
    @TableField("state")
    private Byte state;

    /**
     * 是否是管理者
     */
    @TableField("is_manager")
    private Byte isManager;

    /**
     * 头像
     */
    @TableField("head_img")
    private String headImg;

    /**
     * 入职日期
     */
    @TableField("hire_date")
    private LocalDate hireDate;

    /**
     * 离职日期
     */
    @TableField("fire_date")
    private LocalDate fireDate;

    /**
     * 介绍
     */
    @TableField("intro")
    private String intro;

    /**
     * 创建时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    @TableField("edit_time")
    private LocalDateTime editTime;

    /**
     * 创建人
     */
    @TableField("creator")
    private Long creator;

    /**
     * 编辑人
     */
    @TableField("editor")
    private Long editor;

    /**
     * 是否删除（逻辑删除）
     */
    @TableLogic
    @TableField("deleted")
    private Byte deleted;

    /**
     * 密码
     */
    @TableField("password")
    private String password;

    /**
     * 课时费
     */
    @TableField("class_fee")
    private BigDecimal classFee;

    /**
     * 助教费
     */
    @TableField("assistant_fee")
    private BigDecimal assistantFee;

    /**
     * STAFF所属组织ID
     */
    @TableField("org_id")
    private Long orgId;

    /**
     * 是否内部人员
     */
    @TableField("is_inner")
    private Byte isInner;
}