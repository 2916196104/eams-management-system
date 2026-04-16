package com.zeroone.star.project.dto.j7.operation;


import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

/**
 * 运营界面里积分记录管理的调整积分类
 */

@Data
@ApiModel("调整积分对象")
public class PointsRecordUpdateDTO {
    @ApiModelProperty(value = "学生名称", example = "张三")
    @NotBlank(message = "请选择")
    private String name;
    @ApiModelProperty(value = "调整积分数", example = "1")
    @NotNull(message = "扣减请写成负数")
    private Integer point;
    @ApiModelProperty(value = "调整原因", example = "鉴于该同学表现优异...")
    private String content;
}
