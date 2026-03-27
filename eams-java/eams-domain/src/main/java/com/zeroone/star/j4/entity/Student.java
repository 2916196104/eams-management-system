package com.zeroone.star.j4.entity;

import com.baomidou.mybatisplus.annotation.*;
import java.io.Serializable;
import java.time.LocalDate;
import java.time.LocalDateTime;
import lombok.Getter;
import lombok.Setter;

/**
 * 学员基础信息表 (对应 zo_eams.sql 中的 student 表)
 */
@Getter
@Setter
@TableName("student")
public class Student implements Serializable {

    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    private Long userId;          // 家长id
    private Integer familyRel;    // 家庭关系
    private Boolean asDefault;    // 家长默认查看
    private Long schoolId;        // 所属分校
    private String name;          // 姓名

    @TableLogic
    private Integer deleted;      // 逻辑删除

    private Integer stage;        // 阶段状态
    private Integer gender;       // 性别
    private LocalDate birthday;   // 生日

    /** 核心字段：头像URL */
    private String headImg;

    private Long joinWay;         // 加入方式
    private String remark;        // 备注
    private LocalDate graduationDate;
    private String graduationReason;

    private LocalDateTime addTime; // 加入时间
    private Long counselor;       // 顾问
    private Long creator;
    private Long editor;
    private LocalDateTime editTime;
    private String idcard;        // 身份证号
    private LocalDateTime redpointGrade;
    private LocalDateTime redpointEvaluate;
    private Integer grade;         // 入学年份
    private LocalDate joinDate;    // 入学日期
    private Long wxAccessId;
    private Integer credit;        // 积分
    private Long orgId;
    private Integer gradeId;       // 年级ID
}
