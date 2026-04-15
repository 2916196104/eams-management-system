package com.zeroone.star.project.dto.j5.classmanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

@Data
@ApiModel(value = "调班班级学生传输对象", description = "批量调班的请求参数")
public class TransClassStudentDTO {

    @ApiModelProperty(value = "调入的班级id", required = true, example = "1")
    private Long classId;

    @ApiModelProperty(value = "添加的所有学生的id", required = true, example = "1")
    private List<Long> studentIds;

    @ApiModelProperty(value = "批量调班的目标班级id", required = true, example = "1")
    private Long targetClassId;

}
