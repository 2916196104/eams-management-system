package com.zeroone.star.project.dto.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Date;

@Data
@NoArgsConstructor
@AllArgsConstructor
@ApiModel("调整积分")
public class ChangeCreditDTO {

    @ApiModelProperty(value = "学员id", example = "20260316",required=true)
    private String student_id;
    @ApiModelProperty(value = "课程id", example = "114514",required=true)
    private String course_id;
    @ApiModelProperty(value = "课次id", example = "1919810",required=true)
    private String lesson_id;
    @ApiModelProperty(value = "变更课次数", example = "50",required=true)
    private String change_count;
//    @ApiModelProperty(value = "剩余数量", example = "100")
//    private String remaining_count;
    @ApiModelProperty(value = "操作人", example = "张三")
    private String staff_id;
    @ApiModelProperty(value = "时间", example = "2026-3-15",required=true)
    private Date add_time;
//    @ApiModelProperty(value = "变更阶段", example = "1")
//    private String stage;
    @ApiModelProperty(value = "其他说明", example = "无",required=false)
    private String remark;
}