package com.zeroone.star.project.dto.j4.graduate;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.time.LocalDate;

/**
 * 结业学员导出请求DTO
 */
@Data
@ApiModel(description = "结业学员导出请求DTO")
public class GraduateStudentExportDTO {
    @ApiModelProperty(value = "学员ID（模糊查询）", example = "2024")
    private String studentId;
    @ApiModelProperty(value = "班级名称（模糊查询）", example = "高三")
    private String className;
    @ApiModelProperty(value = "结业时间起始", example = "2024-01-01")
    private LocalDate graduateTimeStart;
    @ApiModelProperty(value = "结业时间结束", example = "2024-12-31")
    private LocalDate graduateTimeEnd;
    @ApiModelProperty(value = "结业状态（1已结业/0未结业）", example = "1")
    private Integer graduateStatus;
}