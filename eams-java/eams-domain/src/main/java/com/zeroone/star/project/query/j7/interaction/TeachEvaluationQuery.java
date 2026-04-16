package com.zeroone.star.project.query.j7.interaction;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;

import java.time.LocalDateTime;

/**
 * 学生评价教师查询条件
 * 贴合数据库字段 + 原型图筛选条件（开始/结束日期、老师/学生/课次） + 分页支持30/50/100/200条/页
 */
@ApiModel(value = "TeachEvaluationQuery", description = "学生评价教师-分页查询条件")
@Data
@EqualsAndHashCode(callSuper = true)
public class TeachEvaluationQuery extends PageQuery {

    // 初始化默认分页：30条/页（原型图默认）
    public TeachEvaluationQuery() {
        super();
        this.setPageSize(30L);  // 默认30条/页，支持切换50/100/200
        this.setPageIndex(1L);
    }

    // 数据库字段：teacher_id → 原型图筛选条件：老师
    @ApiModelProperty(value = "老师ID（筛选条件）", example = "2001", required = false)
    private Long teacherId;

    // 数据库字段：student_id → 原型图筛选条件：学生
    @ApiModelProperty(value = "学生ID（筛选条件）", example = "3001", required = false)
    private Long studentId;

    // 数据库字段：lesson_id → 原型图筛选条件：课次
    @ApiModelProperty(value = "课次ID（筛选条件）", example = "1001", required = false)
    private Long lessonId;

    // 原型图筛选条件：开始日期（对应数据库add_time）
    @ApiModelProperty(value = "评价开始时间（筛选条件，格式：yyyy-MM-dd HH:mm:ss）", example = "2026-03-01 00:00:00", required = false)
    private LocalDateTime addTimeStart;

    // 原型图筛选条件：结束日期（对应数据库add_time）
    @ApiModelProperty(value = "评价结束时间（筛选条件，格式：yyyy-MM-dd HH:mm:ss）", example = "2026-03-31 23:59:59", required = false)
    private LocalDateTime addTimeEnd;
}