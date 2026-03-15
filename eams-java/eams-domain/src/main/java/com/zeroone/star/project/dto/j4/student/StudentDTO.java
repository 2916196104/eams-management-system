package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

//StudentDTO：包含学员基础信息及扩展属性。
@Data // 核心注解：自动生成getter/setter/toString/equals/hashCode
@ApiModel(description = "学员数据传输对象")
public class StudentDTO {

    @ApiModelProperty(value = "学员ID", example = "1001")
    private String studentId;

    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String studentName;

    // 其他字段...
}