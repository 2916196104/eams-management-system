package com.zeroone.star.project.vo.j7.interaction;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * 成绩列表返回VO
 * 贴合数据库字段 + 原型图展示字段（考核项/考核说明/发布者/发布时间）；操作字段标注非开发范围
 * 数据库映射：grade_id=考核项关联ID / add_time=发布时间 / creator=发布者ID
 */
@ApiModel(value = "GradeRecordVO", description = "成绩列表-返回数据")
@Data
public class GradeRecordVO {
    // 原型图展示：考核项（关联grade_id查询考核名称）
    @ApiModelProperty(value = "考核项", example = "Java期末考核")
    private String gradeItem;

    // 原型图展示：考核说明（关联grade_id查询考核描述）
    @ApiModelProperty(value = "考核说明", example = "涵盖Java基础、集合、IO流等知识点")
    private String gradeDescription;

    // 原型图展示：发布者（关联creator查询老师姓名）
    @ApiModelProperty(value = "发布者", example = "李四老师")
    private String creatorName;

    // 数据库字段：add_time → 原型图展示：发布时间
    @ApiModelProperty(value = "发布时间", example = "2026-03-11 10:00:00")
    private LocalDateTime addTime;

    // 原型图展示：操作（删除/修改按钮，非当前开发范围，隐藏）
    @ApiModelProperty(value = "操作（非当前开发范围，展示删除/修改按钮）", hidden = true)
    private String operation;

    @ApiModelProperty(value = "学生姓名", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "成绩分数", example = "95")
    private Integer score;

    // 数据库保留字段（非展示字段，隐藏）
    @ApiModelProperty(value = "成绩记录ID", hidden = true)
    private Long id;
    @ApiModelProperty(value = "考核ID", hidden = true)
    private Long gradeId;
    @ApiModelProperty(value = "学生ID", hidden = true)
    private Long studentId;
    @ApiModelProperty(value = "发布者ID", hidden = true)
    private Long creator;
}