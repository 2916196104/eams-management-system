package com.zeroone.star.project.dto.j7.interaction;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * 学生成绩记录DTO（1:1映射grade_record数据库表）
 * 作用：数据传输/数据库交互，仅保留表中原始字段，无关联扩展字段
 */
@ApiModel(value = "GradeRecordDTO", description = "学生成绩记录-DTO（对应grade_record表）")
@Data
@TableName("grade_record") // 绑定数据库表名，MyBatis-Plus自动识别
public class GradeRecordDTO {
    @ApiModelProperty(value = "成绩ID（主键）", example = "1")
    private Long id; // 对应表id字段（bigint）

    @ApiModelProperty(value = "考核项ID", example = "5001")
    @TableField("grade_id") // 显式绑定表字段（避免驼峰命名适配问题）
    private Long gradeId; // 对应表grade_id字段（bigint）

    @ApiModelProperty(value = "学生ID", example = "3001")
    @TableField("student_id")
    private Long studentId; // 对应表student_id字段（bigint）

    @ApiModelProperty(value = "成绩分数", example = "90")
    @TableField("score")
    private Integer score; // 对应表score字段（tinyint）

    @ApiModelProperty(value = "成绩录入时间", example = "2026-03-16 10:00:00")
    @TableField("add_time")
    private LocalDateTime addTime; // 对应表add_time字段（datetime）

    @ApiModelProperty(value = "录入人ID（教师ID）", example = "2001")
    @TableField("creator")
    private Long creator; // 对应表creator字段（bigint）
}