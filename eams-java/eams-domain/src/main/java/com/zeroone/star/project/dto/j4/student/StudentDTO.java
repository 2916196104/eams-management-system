package com.zeroone.star.project.dto.j4.student;
//StudentDTO：包含学员基础信息及扩展属性。

import io.swagger.annotations.ApiModelProperty;

/**
 * 学生数据传输对象(StudentDTO)类
 * 用于封装和传输学生相关信息的数据结构
 */
public class StudentDTO {
    @ApiModelProperty(value = "学生姓名",example = "张三")
    private String name;// 学生姓名
    @ApiModelProperty(value = "学生ID",example = "1001")
    private  Long id;
}
