package com.zeroone.star.project.dto.j4.graduate;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

/**
 * 结业学员导入DTO（与数据库表字段对齐）
 *
 *
 */
@Data
@ApiModel(description = "结业学员导入DTO")
public class GraduateStudentImportDTO {

    @ApiModelProperty(value = "学员ID（必填，默认值：2024001）", example = "2024001", required = true)
    private String studentId;

    @ApiModelProperty(value = "学员姓名（必填，默认值：张三）", example = "张三", required = true)
    private String studentName;

    @ApiModelProperty(value = "性别（1-男 2-女，默认值：1）", example = "1")
    private Integer gender;

    @ApiModelProperty(value = "身份证号（必填，默认值：110101199001011234）", example = "110101199001011234", required = true)
    private String idCard;

    @ApiModelProperty(value = "所属班级（默认值：高三1班）", example = "高三1班")
    private String className;

    @ApiModelProperty(value = "结业时间（默认值：2024-06-30）", example = "2024-06-30")
    private LocalDate graduateTime;

    @ApiModelProperty(value = "结业状态（1-已结业 0-未结业，默认值：1）", example = "1")
    private Integer graduateStatus;

    @ApiModelProperty(value = "联系方式（默认值：13800138000）", example = "13800138000")
    private String phone;

    @ApiModelProperty(value = "备注（默认值：无）", example = "无")
    private String remark;
}