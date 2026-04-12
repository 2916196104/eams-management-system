package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotEmpty;
import javax.validation.constraints.NotNull;
import java.util.Date;
import java.util.List;

/*
* 添加随课生DTO
* */
@Data
public class CourseStudentDTO {
    @ApiModelProperty("主键ID")
    private Long id;

    @ApiModelProperty(value = "课程ID",example = "17017")
    @NotNull(message = "课程id不能为空")
    private Long lessonId;

    @ApiModelProperty(value = "学生ID(支持多选)",example = "[1,2,3]")
    @NotEmpty(message = "请添加学生")
    private List<Long> studentIds;
//    @ApiModelProperty("学生名称/电话")
//    private String studentNameOrPhone;

//    @ApiModelProperty("学生类型")
//    private int studentType;


}
