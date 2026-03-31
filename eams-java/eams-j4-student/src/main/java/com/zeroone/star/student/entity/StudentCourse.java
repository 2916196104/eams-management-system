package com.zeroone.star.student.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@TableName("student_course")
public class StudentCourse {
    @TableId(type = IdType.AUTO)
    private Long id;
    private Long studentId;
    private Long courseId;
    private Long subjectId;
    private LocalDate startDate;
    private LocalDate expireDate;
    private String remark;
    private Integer countLessonTotal;
    private Integer countLessonComplete;
    private Integer countLessonRefund;
    private BigDecimal courseAmount;
    private BigDecimal discountAmount;
    private BigDecimal amount;
    private BigDecimal paidAmount;
    private Integer payOff;
    private Long operator;
    private Long creator;
    private LocalDateTime addTime;
    private Long editor;
    private LocalDateTime editTime;
    private Integer deleted;
    private Integer verifyState;
    private Integer warningTimes;
    private Integer priority;
    private BigDecimal unitPrice;
    private Integer fromTrial;
    private Long orgId;
    // 我不加这个运行报错，若不影响运行组长可删除
    public void setPayOff(Boolean payOff) {
        // true → 1，false → 0，null → 0
        this.payOff = payOff == null ? 0 : (payOff ? 1 : 0);
    }
    // 数据库不存在，仅用于展示
    @TableField(exist = false)
    private String name;      // 学员姓名
    @TableField(exist = false)
    private String mobile;    // 家长手机号
    @TableField(exist = false)
    private String courseName;// 课程名称（来自 course.name）
    @TableField(exist = false)
    private Integer lessonCount;
    @TableField(exist = false)
    private Integer completeLessonCount;
    @TableField(exist = false)
    private Integer remainingLessonCount;
    @TableField(exist = false)
    private Integer decLessonCount;
}