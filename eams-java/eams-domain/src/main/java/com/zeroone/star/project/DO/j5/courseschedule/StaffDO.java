package com.zeroone.star.project.DO.j5.courseschedule;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import com.baomidou.mybatisplus.annotation.TableLogic;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * 教师员工表 DO
 */
@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
@TableName("staff")
public class StaffDO implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键ID
     */
    @TableId(type = IdType.AUTO)
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
    private LocalDate birthday;

    /**
     * 性别 (0等具体含义视业务而定)
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
     * 在职状态 (默认 1)
     */
    private Integer state;

    /**
     * 是否是管理者 (默认 0)
     */
    private Boolean isManager;

    /**
     * 头像
     */
    private String headImg;

    /**
     * 入职日期
     */
    private LocalDate hireDate;

    /**
     * 离职日期
     */
    private LocalDate fireDate;

    /**
     * 介绍
     */
    private String intro;

    /**
     * 创建时间
     */
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    private LocalDateTime editTime;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 是否删除 (0未删, 1已删)
     */
    @TableLogic
    private Boolean deleted;

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
     * 是否内部人员 (默认 1)
     */
    private Boolean isInner;
}