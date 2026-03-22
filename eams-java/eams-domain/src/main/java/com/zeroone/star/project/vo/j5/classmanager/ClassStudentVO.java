package com.zeroone.star.project.vo.j5.classmanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

@Data

@ApiModel(description = "学员实体")
public class ClassStudentVO {

    @ApiModelProperty(value = "学员ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String name;


    @ApiModelProperty(value = "所属班级ID", example = "5")
    private Long classId;

    @ApiModelProperty(value = "性别 1男 2女", example = "1")
    private Integer gender;

    @ApiModelProperty(value = "联系电话", example = "13800138000")
    private String phone;

    @ApiModelProperty(value = "默认课程", example = "java从入门到入土")
    private String defaultCourse;
}
