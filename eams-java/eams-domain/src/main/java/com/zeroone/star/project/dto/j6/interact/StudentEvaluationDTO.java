package com.zeroone.star.project.dto.j6.interact;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.format.annotation.DateTimeFormat;

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
@ApiModel("教评学数据传输对象")
public class StudentEvaluationDTO implements Serializable {

    @ApiModelProperty(value = "学员", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "课次标题", example = "数据结构")
    private String lessonName;

    @ApiModelProperty(value = "点评得分", example = "5")
    private Integer score;

    @ApiModelProperty(value = "点评内容", example = "学生表现很好，积极参与课堂")
    private String evaluation;

    @ApiModelProperty(value = "点评老师", example = "张老师")
    private String evaluateTeacherName;

    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @ApiModelProperty(value = "点评时间", example = "2024-06-01 12:00")
    private LocalDateTime evaluateTime;
}