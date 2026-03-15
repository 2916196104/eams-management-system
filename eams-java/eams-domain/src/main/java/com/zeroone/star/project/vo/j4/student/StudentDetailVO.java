package com.zeroone.star.project.vo.j4.student;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

//StudentDetailVO：详情页使用，包含报名记录、积分、历史记录。
@Data
@ApiModel(description = "学员详情响应对象")
public class StudentDetailVO {

    @ApiModelProperty(value = "学员ID", example = "1001")
    private String studentId;

    @ApiModelProperty(value = "学员姓名", example = "测试学员")
    private String studentName;

    // 其他字段...
}