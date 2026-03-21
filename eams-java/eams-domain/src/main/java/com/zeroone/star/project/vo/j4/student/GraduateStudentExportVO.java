package com.zeroone.star.project.vo.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

/**
 * 结业学员导出VO
 *
 *
 */
@Data
@ApiModel(description = "结业学员导出VO")
public class GraduateStudentExportVO {

    @ApiModelProperty(value = "学员ID", example = "2024001")
    private String studentId;

    @ApiModelProperty(value = "学员姓名", example = "张三")
    private String studentName;

    @ApiModelProperty(value = "性别（中文展示）", example = "男")
    private String genderName;

    @ApiModelProperty(value = "身份证号", example = "110101199001011234")
    private String idCard;

    @ApiModelProperty(value = "所属班级", example = "高三1班")
    private String className;

    @ApiModelProperty(value = "结业时间", example = "2024-06-30")
    private LocalDate graduateTime;

    @ApiModelProperty(value = "结业状态（中文展示）", example = "已结业")
    private String graduateStatusName;

    @ApiModelProperty(value = "联系方式", example = "13800138000")
    private String phone;

    @ApiModelProperty(value = "备注", example = "无")
    private String remark;
}