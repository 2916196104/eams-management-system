package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModelProperty;

import java.time.LocalDate;

//StudentDTO：包含学员基础信息及扩展属性。
public class StudentDTO {

    @ApiModelProperty(value = "姓名", example = "张三")
    private String name;

    @ApiModelProperty(value = "性别")
    private Integer gender;

    @ApiModelProperty(value = "生日")
    private LocalDate birthday;

    @ApiModelProperty(value = "阶段状态 0意向学员")
    private Integer stage;

}
