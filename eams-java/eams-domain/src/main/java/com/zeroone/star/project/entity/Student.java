package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.Year;

/**
 * <p>
 * 学生表
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-19
 */
@Data
@TableName("student")
public class Student implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /**
     * 家长 id
     */
    private Long userId;

    /**
     * 家庭关系
     */
    private Integer familyRel;

    /**
     * 家长默认查看的学员
     */
    private Integer asDefault;

    /**
     * 所属分校
     */
    private Long schoolId;

    /**
     * 姓名
     */
    private String name;

    /**
     * 逻辑删除
     */
    private Integer deleted;

    /**
     * 阶段状态 0 意向学员
     */
    private Integer stage;

    /**
     * 性别
     */
    private Integer gender;

    /**
     * 生日
     */
    private LocalDate birthday;

    /**
     * 头像
     */
    private String headImg;

    /**
     * 加入方式
     */
    private Long joinWay;

    /**
     * 备注
     */
    private String remark;

    /**
     * 结业日期
     */
    private LocalDate graduationDate;

    /**
     * 结业原因
     */
    private String graduationReason;

    /**
     * 加入时间
     */
    private LocalDateTime addTime;

    /**
     * 顾问
     */
    private Long counselor;

    /**
     * 创建者
     */
    private Long creator;

    /**
     * 编辑人
     */
    private Long editor;

    /**
     * 编辑时间
     */
    private LocalDateTime editTime;

    /**
     * 身份证号
     */
    private String idcard;

    /**
     * 红点标记成绩最后查看时间
     */
    private LocalDateTime redpointGrade;

    /**
     * 红点标记点评最后查看时间
     */
    private LocalDateTime redpointEvaluate;

    /**
     * 入学年份
     */
    private Year grade;

    /**
     * 入学日期
     */
    private LocalDate joinDate;

    /**
     * 微信登录记录 id
     */
    private Long wxAccessId;

    /**
     * 学生积分
     */
    private Integer credit;

    /**
     * 创建者所属组织 ID
     */
    private Long orgId;

    /**
     * 年级 ID
     */
    private Integer gradeId;
}
