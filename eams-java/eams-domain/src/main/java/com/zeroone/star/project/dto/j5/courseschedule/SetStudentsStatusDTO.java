package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModelProperty;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.List;

public class SetStudentsStatusDTO {
    @ApiModelProperty(value = "课次学员记录ID列表", required = true)
    List<Long> lessonStudentIds;
    @ApiModelProperty(value = "目标状态", required = true)
    String status;
}
