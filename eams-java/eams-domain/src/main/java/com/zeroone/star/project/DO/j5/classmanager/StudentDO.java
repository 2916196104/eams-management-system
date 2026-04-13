package com.zeroone.star.project.DO.j5.classmanager;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import com.baomidou.mybatisplus.annotation.TableLogic;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.Year;

/**
 * @author silvan
 * @description 学生表
 */
@TableName("student")
@Data
public class StudentDO {

    /**
     * 主键ID
     */
    @TableId(type = IdType.ASSIGN_ID)
    private Long id;


    /**
     * 家长id（主键）
     */

    @TableField("user_id")
    private Long userId;

    /**
     * 家庭关系
     */
    @TableField("family_rel")
    private Byte familyRel;

    /**
     * 家长默认查看的学员
     */
    @TableField("as_default")
    private Byte asDefault;

    /**
     * 所属分校
     */
    @TableField("school_id")
    private Long schoolId;

    /**
     * 姓名
     */
    @TableField("name")
    private String name;

    /**
     * 逻辑删除
     */
    @TableLogic
    @TableField("deleted")
    private Integer deleted;

    /**
     * 阶段状态0意向学员
     */
    @TableField("stage")
    private Byte stage;

    /**
     * 性别
     */
    @TableField("gender")
    private Byte gender;

    /**
     * 生日
     */
    @TableField("birthday")
    private LocalDate birthday;

    /**
     * 头像
     */
    @TableField("head_img")
    private String headImg;

    /**
     * 加入方式
     */
    @TableField("join_way")
    private Long joinWay;

    /**
     * 备注
     */
    @TableField("remark")
    private String remark;

    /**
     * 结业日期
     */
    @TableField("graduation_date")
    private LocalDate graduationDate;

    /**
     * 结业原因
     */
    @TableField("graduation_reason")
    private String graduationReason;

    /**
     * 加入时间
     */
    @TableField("add_time")
    private LocalDateTime addTime;

    /**
     * 顾问
     */
    @TableField("counselor")
    private Long counselor;

    /**
     * 创建者
     */
    @TableField("creator")
    private Long creator;

    /**
     * 编辑人
     */
    @TableField("editor")
    private Long editor;

    /**
     * 编辑时间
     */
    @TableField("edit_time")
    private LocalDateTime editTime;

    /**
     * 身份证号
     */
    @TableField("idcard")
    private String idcard;

    /**
     * 红点标记成绩最后查看时间
     */
    @TableField("redpoint_grade")
    private LocalDateTime redpointGrade;

    /**
     * 红点标记点评最后查看时间
     */
    @TableField("redpoint_evaluate")
    private LocalDateTime redpointEvaluate;

    /**
     * 入学年份
     */
    @TableField("grade")
    private Year grade;

    /**
     * 入学日期
     */
    @TableField("join_date")
    private LocalDate joinDate;

    /**
     * 微信登录记录id
     */
    @TableField("wx_access_id")
    private Long wxAccessId;

    /**
     * 学生积分
     */
    @TableField("credit")
    private Integer credit;

    /**
     * 创建者所属组织ID
     */
    @TableField("org_id")
    private Long orgId;
}