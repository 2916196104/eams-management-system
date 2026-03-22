package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModelProperty;

public class EvaluationDTO {
    @ApiModelProperty("主键id，评价序号")
    private Long id;

    @ApiModelProperty("老师id")
    private Long teacherId;
    @ApiModelProperty("老师姓名")
    private String teacherName;

    @ApiModelProperty("学生id")
    private Long studentId;
    @ApiModelProperty("学生姓名")
    private String studentName;

    @ApiModelProperty("课次id")
    private Long lessonId;
    @ApiModelProperty("课程标题")
    private String courseTitle;

    @ApiModelProperty(value = "综合评分（1-5星）", example = "5")
    private Integer overallScore;

    @ApiModelProperty(value = "课堂气氛（1-5星）", example = "5")
    private Integer atmosphereScore;

    @ApiModelProperty(value = "授课态度（1-5星）", example = "5")
    private Integer attitudeScore;

    @ApiModelProperty(value = "教学效果（1-5星）", example = "5")
    private Integer effectScore;

    @ApiModelProperty(value = "评价内容", example = "还是不错的")
    private String content;

}
