package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

@Data
@ApiModel("学员课程进度还原 DTO")
public class RollBackDTO {

    @ApiModelProperty(value = "课次ID", example = "1001")
    private Long lessonId;

    @ApiModelProperty(value = "课次学员记录ID列表（支持多选）", required = true, example = "[1001, 1002]")
    private List<Long> lessonStudentIds;
}
