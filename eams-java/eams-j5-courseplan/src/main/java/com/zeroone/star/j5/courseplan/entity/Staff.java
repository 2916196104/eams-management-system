package com.zeroone.star.j5.courseplan.entity;

import com.baomidou.mybatisplus.annotation.*;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * <p>
 * 教师员工表 Entity
 * </p>
 *
 * @author taohu5564
 * @since 2026-03-18
 */
@Data
@TableName("staff")
public class Staff {
    /**
     * 主键 ID
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
     * 微信登录 ID
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
     * 性别 (1:男, 2:女, 0:未知)
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
     * 学历 (1:高中, 2:大专, 3:本科, 4:硕士, 5:博士)
     */
    private Integer degree;

    /**
     * 备注
     */
    private String remark;

    /**
     * 在职状态 (1:在职, 0:离职)
     */
    private Integer state;

    /**
     * 是否是管理者 (1:是, 0:否)
     */
    private Boolean isManager;

    /**
     * 头像路径
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
    @TableField(fill = FieldFill.INSERT)
    private LocalDateTime addTime;

    /**
     * 编辑时间
     */
    @TableField(fill = FieldFill.INSERT_UPDATE)
    private LocalDateTime editTime;

    /**
     * 创建人 ID
     */
    private Long creator;

    /**
     * 编辑人 ID
     */
    private Long editor;

    /**
     * 逻辑删除标记 (0:未删除, 1:已删除)
     */
    @TableLogic
    private Integer deleted;

    /**
     * 密码 (注意：查询列表时建议忽略此字段)
     */
    @TableField(select = false) // 默认查询不select该字段，保护安全
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
     * 所属组织 ID
     */
    private Long orgId;

    /**
     * 是否内部人员 (1:是, 0:否)
     */
    private Boolean isInner;
}

