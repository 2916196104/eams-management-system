package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

@Data
@ApiModel("批量停复课 DTO")
public class CoursePauseResumeDTO {

    @ApiModelProperty(value = "课次ID列表", required = true, example = "[1001, 1002]")
    private List<Long> lessonIds;


    @ApiModelProperty(value = "是否复课", notes = "true=复课，false=停课",
            required = true, example = "false")
    private Boolean isResume;
}
