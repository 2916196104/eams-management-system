package com.zeroone.star.project.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * 课程体验卡 实体类（对应数据库表 course_trial）
 */
@Data
@TableName("course_trial")
public class CourseTrial {

    // 主键
    @TableId(type = IdType.INPUT)
    private Long id;

    // 课程ID
    private Long courseId;

    // 名称
    private String title;

    // 发行数量
    private Integer quantity;

    // 剩余数量
    private Integer remainingQuantity;

    // 课时数
    private Integer lessonCount;

    // 领取后有效天数
    private Integer expireDays;

    // 发行结束日期
    private LocalDate endDate;

    // 启用状态
    private Integer state;

    // 创建人
    private Long creator;

    // 编辑人
    private Long editor;

    // 添加时间
    private LocalDateTime addTime;

    // 编辑时间
    private LocalDateTime editTime;

    // 删除标记
    private Integer deleted;

    // 创建者所属组织ID
    private Long orgId;
}