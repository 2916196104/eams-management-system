package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;

@Data
@ApiModel(value = "修改头像DTO")
public class StudentDTO implements Serializable {
    @ApiModelProperty(value = "学员ID", example = "1001", required = true)
    private Long id; // 对应 student.id

    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String name; // 对应 student.name

    @ApiModelProperty(value = "头像地址", example = "group1/M00/00/01/a.png")
    private String headImg; // 对应 student.head_img
}
