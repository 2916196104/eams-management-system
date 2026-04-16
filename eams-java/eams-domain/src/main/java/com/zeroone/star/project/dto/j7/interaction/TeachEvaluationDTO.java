package com.zeroone.star.project.dto.j7.interaction;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * 学生点评教师DTO（对应teach_evaluation表）
 */
@ApiModel(value = "TeachEvaluationDTO", description = "学生点评教师-DTO（多维度评价）")
@Data
@TableName("teach_evaluation") // 绑定数据库表名
public class TeachEvaluationDTO {
    @ApiModelProperty(value = "评价ID", example = "1")
    private Long id; // 主键ID

    @ApiModelProperty(value = "课次ID", example = "1001")
    @TableField("lesson_id") // 匹配表字段
    private Long lessonId;

    @ApiModelProperty(value = "被评价教师ID", example = "2001")
    @TableField("teacher_id")
    private Long teacherId;

    @ApiModelProperty(value = "综合评分", example = "90")
    @TableField("score1") // 维度1：综合评分
    private Integer score1;

    @ApiModelProperty(value = "课堂气氛评分", example = "95")
    @TableField("score2") // 维度2：课堂气氛
    private Integer score2;

    @ApiModelProperty(value = "授课态度评分", example = "88")
    @TableField("score3") // 维度3：授课态度
    private Integer score3;

    @ApiModelProperty(value = "教学效果评分", example = "92")
    @TableField("score4") // 维度4：教学效果
    private Integer score4;

    @ApiModelProperty(value = "评价内容", example = "老师讲课生动，课堂气氛活跃")
    @TableField("content")
    private String content;

    @ApiModelProperty(value = "评价时间", example = "2026-03-16 15:30:00")
    @TableField("add_time")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "评价学生ID", example = "3001")
    @TableField("student_id")
    private Long studentId;

    @ApiModelProperty(value = "是否匿名（1=匿名，0=非匿名）", example = "1")
    @TableField("anonymity")
    private Integer anonymity;

    @ApiModelProperty(value = "机构ID", example = "101")
    @TableField("org_id")
    private Long orgId;
}