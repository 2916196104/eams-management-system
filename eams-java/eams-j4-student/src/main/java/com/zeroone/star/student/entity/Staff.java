package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import java.io.Serializable;
import java.math.BigDecimal;
import java.util.Date;

/**
 * 教师员工表 DO
 * 类名首字母大写，字段名与数据库完全一致
 * 对应数据库表：staff
 */
@Data
@TableName("staff") // 表名与数据库一致
public class Staff implements Serializable {
    private static final long serialVersionUID = 1L;

    /**
     * 主键（数据库字段：id）
     */
    @TableId(type = IdType.AUTO)
    private Long id;

    /**
     * 姓名（数据库字段：name）
     */
    private String name;

    /**
     * 手机号（数据库字段：mobile）
     */
    private String mobile;

    /**
     * 微信登录id（数据库字段：wx_access_id）
     */
    private Long wx_access_id;

    /**
     * EMAIL（数据库字段：email）
     */
    private String email;

    /**
     * 生日（数据库字段：birthday）
     */
    private Date birthday;

    /**
     * 性别（数据库字段：gender）
     */
    private Integer gender;

    /**
     * 身份证（数据库字段：id_card）
     */
    private String id_card;

    /**
     * 毕业学校（数据库字段：school）
     */
    private String school;

    /**
     * 学历（数据库字段：degree）
     */
    private Integer degree;

    /**
     * 备注（数据库字段：remark）
     */
    private String remark;

    /**
     * 在职状态（数据库字段：state）
     */
    private Integer state;

    /**
     * 是否是管理者（数据库字段：is_manager）
     */
    private Integer is_manager;

    /**
     * 头像（数据库字段：head_img）
     */
    private String head_img;

    /**
     * 入职日期（数据库字段：hire_date）
     */
    private Date hire_date;

    /**
     * 离职日期（数据库字段：fire_date）
     */
    private Date fire_date;

    /**
     * 介绍（数据库字段：intro）
     */
    private String intro;

    /**
     * 创建时间（数据库字段：add_time）
     */
    private Date add_time;

    /**
     * 编辑时间（数据库字段：edit_time）
     */
    private Date edit_time;

    /**
     * 创建人（数据库字段：creator）
     */
    private Long creator;

    /**
     * 编辑人（数据库字段：editor）
     */
    private Long editor;

    /**
     * 是否删除（数据库字段：deleted）
     */
    @TableLogic
    private Integer deleted;

    /**
     * 密码（数据库字段：password）
     */
    private String password;

    /**
     * 课时费（数据库字段：class_fee）
     */
    private BigDecimal class_fee;

    /**
     * 助教费（数据库字段：assistant_fee）
     */
    private BigDecimal assistant_fee;

    /**
     * STAFF所属组织ID（数据库字段：org_id）
     */
    private Long org_id;

    /**
     * 是否内部人员（数据库字段：is_inner）
     */
    private Integer is_inner;
}