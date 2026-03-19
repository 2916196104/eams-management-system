package com.zeroone.star.project.vo.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.ArrayList;
import java.util.List;

/**
 * 结业学员导入结果VO
 *
 *
 */
@Data
@ApiModel(description = "结业学员导入结果VO")
public class GraduateStudentImportResultVO {

    @ApiModelProperty(value = "成功条数", example = "1")
    private Integer successCount;
    @ApiModelProperty(value = "失败条数", example = "0")
    private Integer failCount;
    @ApiModelProperty(value = "失败详情", example = "[]")
    private List<String> failDetails;
    @ApiModelProperty(value = "批次号", example = "B2024063001")
    private String batchNo;
}