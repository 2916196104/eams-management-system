package com.zeroone.star.project.query.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
@ApiModel("调整积分")
public class ChangeCreditQuery {

    @ApiModelProperty(value = "学员id", example = "20260316",required=true)
    private String student_id;
    @ApiModelProperty(value = "调整积分数", example = "+30",required=true)
    private String change_credit;
    @ApiModelProperty(value = "调整原因", example = "无",required=false)
    private String remark;
}