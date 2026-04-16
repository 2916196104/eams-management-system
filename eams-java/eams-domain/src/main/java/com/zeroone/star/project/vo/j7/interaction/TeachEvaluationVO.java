package com.zeroone.star.project.vo.j7.interaction;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * 学生评价教师返回VO
 * 贴合数据库字段 + 原型图展示字段（序号/学员/老师/课次标题/综合评分/课堂气氛/授课态度/教学效果/评价内容/评价时间）
 * 数据库映射：score1=课堂气氛 / score2=授课态度 / score3=教学效果 / content=评价内容 / add_time=评价时间
 */
@ApiModel(value = "TeachEvaluationVO", description = "学生评价教师-列表返回数据")
@Data
public class TeachEvaluationVO {
    // 原型图展示：序号
    @ApiModelProperty(value = "序号", example = "1")
    private Integer serialNumber;

    // 原型图展示：学员（关联student_id查询姓名）
    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String studentName;

    // 原型图展示：老师（关联teacher_id查询姓名）
    @ApiModelProperty(value = "老师姓名", example = "李四老师")
    private String teacherName;

    // 原型图展示：课次标题（关联lesson_id查询标题）
    @ApiModelProperty(value = "课次标题", example = "Java基础第10讲")
    private String lessonTitle;

    // 原型图展示：综合评分（score1+score2+score3)/3 计算得出
    @ApiModelProperty(value = "综合评分", example = "90")
    private Integer overallScore;

    // 数据库字段：score1 → 原型图展示：课堂气氛
    @ApiModelProperty(value = "课堂气氛评分", example = "95")
    private Integer atmosphereScore; // 对应score1

    // 数据库字段：score2 → 原型图展示：授课态度
    @ApiModelProperty(value = "授课态度评分", example = "92")
    private Integer attitudeScore; // 对应score2

    // 数据库字段：score3 → 原型图展示：教学效果
    @ApiModelProperty(value = "教学效果评分", example = "88")
    private Integer effectScore; // 对应score3

    // 数据库字段：content → 原型图展示：评价内容
    @ApiModelProperty(value = "评价内容", example = "课堂气氛好，老师讲解清晰")
    private String content;

    // 数据库字段：add_time → 原型图展示：评价时间
    @ApiModelProperty(value = "评价时间", example = "2026-03-16 15:30:00")
    private LocalDateTime addTime;

    // 数据库字段：anonymity（保留，非展示字段但需映射）
    @ApiModelProperty(value = "匿名状态（1=匿名，0=实名）", hidden = true)
    private Integer anonymity;

    // 数据库字段：org_id（保留，非展示字段但需映射）
    @ApiModelProperty(value = "机构ID", hidden = true)
    private Long orgId;
}