package com.zeroone.star.project.query.j8.stumanager.common;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.time.LocalDate;

@Data
public class StuClassQuery {
    @ApiModelProperty(value = "学生ID", example = "1")
    private Long studentId;
    @ApiModelProperty(value = "开始时间", example = "10:00", dataType = "java.lang.String")
    private LocalDate beginTime;
    @ApiModelProperty(value = "结束时间", example = "11:30", dataType = "java.lang.String")
    private LocalDate endTime;
}
