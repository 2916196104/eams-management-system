package com.zeroone.star.project.vo.j7.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("试听卡展示对象")
public class TrailCardVO {
    @ApiModelProperty(value = "试听卡ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "试听卡标题", example = "英语体验卡")
    private String title;

    @ApiModelProperty(value = "剩余数量", example = "80")
    private Integer remainingQuantity;

    @ApiModelProperty(value = "课时数", example = "8")
    private Integer lessonCount;

    @ApiModelProperty(value = "可领取状态：true可领取 false不可领取", example = "true")
    private Boolean canReceive;
}
