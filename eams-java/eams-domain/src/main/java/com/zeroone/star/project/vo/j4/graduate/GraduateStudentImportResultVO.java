package com.zeroone.star.project.vo.j4.graduate;

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

    @ApiModelProperty(value = "成功导入数量（默认值：1）", example = "1")
    private Integer successCount = 1;

    @ApiModelProperty(value = "失败导入数量（默认值：0）", example = "0")
    private Integer failCount = 0;

    @ApiModelProperty(value = "失败详情（默认值：空列表）", example = "[]")
    private List<String> failMsgList = new ArrayList<>();
}