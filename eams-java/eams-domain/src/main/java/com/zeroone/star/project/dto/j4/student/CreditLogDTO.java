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

    @ApiModelProperty(value = "序号", example = "1")
    private String id;
    @ApiModelProperty(value = "学生姓名", example = "张三")
    private String student_name;
    @ApiModelProperty(value = "变动积分", example = "+10")
    private String change_credit;
    @ApiModelProperty(value = "剩余积分", example = "20")
    private String remain_credit;
    @ApiModelProperty(value = "说明", example = "1,发言 2,迟到")
    private String change_reason;
    @ApiModelProperty(value = "其他说明", example = "无")
    private String remark;
    @ApiModelProperty(value = "变动时间", example = "2026-3-16")
    private String change_time;
}
