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
 * 学员表
 * </p>
 * @author hxb
 */
@Getter
@Setter
@TableName("student")
public class StudentDO implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

    /**
     * 家长id
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
     * 阶段状态0意向学员
     */
    private Integer stage;

    /**
     * 性别
     */
    private Integer gender;

    /**
     * 生日
     */
    private Date birthday;

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
    private Date graduationDate;

    /**
     * 结业原因
     */
    private String graduationReason;

    /**
     * 加入时间
     */
    private Date addTime;

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
    private Date editTime;

    /**
     * 身份证号
     */
    private String idcard;

    /**
     * 入学年份
     */
    private Date grade;

    /**
     * 入学日期
     */
    private Date joinDate;

    /**
     * 微信登录记录id
     */
    private Long wxAccessId;

    /**
     * 学生积分
     */
    private Integer credit;

    /**
     * 创建者所属组织ID
     */
    private Long orgId;

    /**
     * 年级ID
     */
    private Integer gradeId;
}
