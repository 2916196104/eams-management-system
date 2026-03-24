package com.zeroone.star.j1.console.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;
import java.util.Date;

/**
 * <p>
 * 课程表（课次表）
 * </p>
 * @author hxb
 */
@Getter
@Setter
@TableName("lesson")
public class LessonDO implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;

    /**
     * 课程标题
     */
    private String title;

    /**
     * 课节数 第几节课
     */
    private Integer sn;

    /**
     * 课程id
     */
    private Long courseId;

    /**
     * 编排计划id
     */
    private Long scheduleId;

    /**
     * 班级id
     */
    private Long classId;

    /**
     * 教室id
     */
    private Long roomId;

    /**
     * 上课日期
     */
    private Date date;

    /**
     * 开始时间
     */
    private Date startTime;

    /**
     * 结束时间
     */
    private Date endTime;

    /**
     * 创建人
     */
    private Long creator;

    /**
     * 编辑者
     */
    private Long editor;

    /**
     * 添加时间
     */
    private Date addTime;

    /**
     * 修改时间
     */
    private Date editTime;

    /**
     * 删除标记
     */
    private Integer deleted;

    /**
     * 应扣课次数
     */
    private Integer decCount;

    /**
     * 备注
     */
    private String remark;

    /**
     * 授课方式
     */
    private Integer teachType;

    /**
     * 是否开启试听
     */
    private Integer onTrial;

    /**
     * 试听结果
     */
    private String trialResult;

    /**
     * 课次状态
     */
    private Integer state;

    /**
     * 结课时间
     */
    private Date closeTime;

    /**
     * 结课人
     */
    private Long closeOperator;

    /**
     * 主讲人(只用于数据权限)
     */
    private Long teacherId;

    /**
     * 是否开放预约
     */
    private Integer bookable;

    /**
     * 老师所属学校ID
     */
    private Long schoolId;

    /**
     * 创建者所属组织ID
     */
    private Long orgId;
}
