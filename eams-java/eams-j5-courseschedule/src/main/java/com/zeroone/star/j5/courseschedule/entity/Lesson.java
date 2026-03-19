package com.zeroone.star.j5.courseschedule.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableLogic;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;

/**
 * <p>
 * 描述：课次实体类
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
@Data
@TableName("lesson")
public class Lesson implements Serializable {
    private static final long serialVersionUID = 1L;

    @TableId(value = "id", type = IdType.ASSIGN_ID)
    private Long id;

    /** 课程标题 */
    private String title;

    /** 课节数 第几节课 */
    private Integer sn;

    /** 课程id */
    private Long courseId;

    /** 编排计划id */
    private Long scheduleId;

    /** 班级id */
    private Long classId;

    /** 教室id */
    private Long roomId;

    /** 上课日期 */
    private LocalDate date;

    /** 开始时间 */
    private LocalTime startTime;

    /** 结束时间 */
    private LocalTime endTime;

    /** 创建人 */
    private Long creator;

    /** 编辑者 */
    private Long editor;

    /** 添加时间 */
    private LocalDateTime addTime;

    /** 修改时间 */
    private LocalDateTime editTime;

    /** 删除标记 */
    @TableLogic
    private Boolean deleted;

    /** 应扣课次数 */
    private Integer decCount;

    /** 备注 */
    private String remark;

    /** 授课方式 */
    private Integer teachType;

    /** 是否开启试听 */
    private Boolean onTrial;

    /** 试听结果 */
    private String trialResult;

    /** 课次状态 0-已停课 1-进行中 2-已结课 */
    private Integer state;

    /** 结课时间 */
    private LocalDateTime closeTime;

    /** 结课人 */
    private Long closeOperator;

    /** 主讲人(只用于数据权限) */
    private Long teacherId;

    /** 是否开放预约 */
    private Boolean bookable;

    /** 老师所属学校ID */
    private Long schoolId;

    /** 创建者所属组织ID */
    private Long orgId;
}
