
package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

// 列表查询响应体（只包含关键数据和唯一标识）
@Data
public class ResponseDTO {

    @ApiModelProperty(value = "学员id(唯一标识)",example = "11111111")
    private Long id;
    @ApiModelProperty(value = "姓名", example = "张三")
    private String name;

}