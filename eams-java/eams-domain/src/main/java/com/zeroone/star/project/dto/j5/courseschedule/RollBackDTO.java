package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

@Data
@ApiModel("学生签到状态还原 DTO")
public class RollBackDTO {

    @ApiModelProperty(value = "课次ID", required = true, example = "1001")
    private Long lessonId;

    @ApiModelProperty(value = "要还原的学生ID列表（支持多选）", required = true, example = "[2001, 2002]")
    private List<Long> studentIds;
}
