package com.zeroone.star.project.query.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

/**
 * 结业学员导出查询条件
 *
 *
 */
@Data
@ApiModel(description = "结业学员导出查询条件")
public class GraduateStudentExportQuery {

    @ApiModelProperty(value = "所属班级", example = "张三")
    private String className;

    @ApiModelProperty(value = "结业状态（1-已结业 0-未结业，默认值：1）", example = "1")
    private Integer graduateStatus;

    @ApiModelProperty(value = "结业开始时间（默认值：2024-01-01）", example = "2024-01-01")
    private LocalDate graduateStartTime;

    @ApiModelProperty(value = "结业结束时间（默认值：2024-12-31）", example = "2024-12-31")
    private LocalDate graduateEndTime;
}