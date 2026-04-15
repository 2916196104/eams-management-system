package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * 描述：班级列表响应 DTO
 *
 */
@Data
public class ClassDTO {

    @ApiModelProperty(value = "班级 ID", hidden = true) // 列表不显示 ID，但逻辑需要
    private Long id;

    @ApiModelProperty(value = "班级名称", required = true, example = "qaweq")
    private String name;

    @ApiModelProperty(value = "科目 (课程名称)", required = true, example = "书法")
    private String subject;

    @ApiModelProperty(value = "教室名称", required = true, example = "木叶村")
    private String classroomName;

    @ApiModelProperty(value = "学生数 (当前人数)", required = true, example = "1")
    private Integer studentCount;

    @ApiModelProperty(value = "人数上限 (预招人数)", required = true, example = "50")
    private Integer maxStudentCount;

    @ApiModelProperty(value = "课程 ID", hidden = true)
    private Long courseId;

    @ApiModelProperty(value = "教室 ID", hidden = true)
    private Long classroomId;
}