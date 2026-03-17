package com.zeroone.star.project.dto.j6.interact;

import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.time.LocalDateTime;


/**
 * <p>
 * 描述：教评学传输对象
 * </p>
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class StudentEvaluationDTO implements Serializable {

    @ApiModelProperty(value = "学生姓名", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "课程名称", example = "数据结构")
    private String lessonName;

    @ApiModelProperty(value = "点评得分", example = "5")
    private Integer score;

    @ApiModelProperty(value = "点评内容", example = "学生表现很好，积极参与课堂")
    private String evaluation;

    @ApiModelProperty(value = "点评老师", example = "张老师")
    private String evaluateTeacherName;

    @ApiModelProperty(value = "点评时间", example = "2024-06-01 12:00")
    private LocalDateTime evaluateTime;
}