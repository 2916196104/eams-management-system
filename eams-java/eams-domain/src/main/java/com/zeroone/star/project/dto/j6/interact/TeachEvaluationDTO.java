package com.zeroone.star.project.dto.j6.interact;


import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.time.LocalDateTime;
import java.util.Date;

/**
 * <p>
 * 描述：学评教传输对象
 * </p>
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class TeachEvaluationDTO implements Serializable {

    @ApiModelProperty(value = "学生姓名", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "老师姓名", example = "张老师")
    private String teacherName;

    @ApiModelProperty(value = "课程名称", example = "数据结构")
    private String lessonName;

    @ApiModelProperty(value = "综合评分", example = "5")
    private Integer score1;

    @ApiModelProperty(value = "课堂气氛", example = "5")
    private Integer score2;

    @ApiModelProperty(value = "授课态度", example = "5")
    private Integer score3;

    @ApiModelProperty(value = "教学效果", example = "5")
    private Integer score4;

    @ApiModelProperty(value = "评价内容", example = "教学效果很好，讲解清晰")
    private String content;

    @ApiModelProperty(value = "评价时间", example = "2024-06-01 12:00")
    private Date addTime;

    //todo 可能需要删除这个字段？
    @ApiModelProperty(value = "是否匿名，默认为否", example = "0")
    private Integer anonymity=0;

}
