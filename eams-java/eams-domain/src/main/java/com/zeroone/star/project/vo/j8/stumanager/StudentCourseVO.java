package com.zeroone.star.project.vo.j8.stumanager;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * <p>
 * 学生表vo
 * </p>
 */
@Data
@ApiModel(value = "StudentCourseVO", description = "学员课程数据展示对象")
public class StudentCourseVO implements Serializable {
    @ApiModelProperty(value = "学员姓名",example = "张三")
    private String studentName;
    @ApiModelProperty(value = "课程名称",example = "写作")
    private String courseName;

    @ApiModelProperty(value = "总课次",example = "24")
    private Integer countLessonTotal;
    @ApiModelProperty(value = "已上课次",example = "5")
    private Integer countLessonComplete;
    @ApiModelProperty(value = "剩余课次",example = "19")
    private Integer countLessonRemaining;

    @ApiModelProperty(value = "正常上课次数", example = "0")
    private Integer attendCount;

    @ApiModelProperty(value = "请假次数", example = "0")
    private Integer leaveCount;

    @ApiModelProperty(value = "旷课次数", example = "0")
    private Integer absentCount;

    @ApiModelProperty(value = "补课次数", example = "0")
    private Integer makeupCount;

}
