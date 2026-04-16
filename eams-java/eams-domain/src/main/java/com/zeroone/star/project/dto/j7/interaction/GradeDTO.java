package com.zeroone.star.project.dto.j7.interaction;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

//成绩单数据传输对象
@Data
public class GradeDTO {
    @ApiModelProperty(value = "id,新增不需要上传唯一 Id，修改要上传唯一 Id", example = "0")
    private long id;

    @ApiModelProperty(value = "考核项", example = "Java 期末考核")
    private String title;

    @ApiModelProperty(value = "考核项说明", example = "涵盖 Java 基础、集合、IO 流等知识点")
    private String info;
}
