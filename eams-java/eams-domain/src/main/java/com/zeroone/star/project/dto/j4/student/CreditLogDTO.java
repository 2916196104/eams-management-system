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
@ApiModel("获取积分记录（条件+分页）")
public class CreditLogDTO {

    @ApiModelProperty(value = "学生id", example = "20260316",required=true)
    private String student_id;
    @ApiModelProperty(value = "学生账号id", example = "114514",required=true)
    private String user_id;
    @ApiModelProperty(value = "变动数量", example = "10",required=true)
    private String credit;
//    @ApiModelProperty(value = "剩余积分数量", example = "50")
//    private String current_credit;
    @ApiModelProperty(value = "变动类型", example = "1,发言 2,迟到",required=true)
    private String change_type;
    @ApiModelProperty(value = "变动时间", example = "2026-3-15",required=true)
    private Date add_time;
    @ApiModelProperty(value = "其他说明", example = "无")
    private String remark;
    @ApiModelProperty(value = "记录来源id", example = "1919810")
    private String source_id;
    @ApiModelProperty(value = "调整人", example = "张三",required=true)
    private String staff_id;
    @ApiModelProperty(value = "学生所属学校ID", example = "01us")
    private String school_id;
}
