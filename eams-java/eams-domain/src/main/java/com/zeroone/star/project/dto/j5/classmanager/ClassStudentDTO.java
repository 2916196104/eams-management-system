package com.zeroone.star.project.dto.j5.classmanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

/**
 * 描述：班级学生传输对象
 */
@Data
@ApiModel(value = "班级学生传输对象", description = "往班级添加学员的请求参数")
public class ClassStudentDTO {
    @ApiModelProperty(value = "加入的班级id", required = true, example = "1")
    private Long classId;

    @ApiModelProperty(value = "添加的所有学生的id", required = true, example = "1,2,3")
    private List<Long> studentIds;

}

