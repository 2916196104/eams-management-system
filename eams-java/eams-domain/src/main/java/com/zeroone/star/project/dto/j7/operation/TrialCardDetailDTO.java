package com.zeroone.star.project.dto.j7.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

@Data
@ApiModel("试听卡详情数据对象")
public class TrialCardDetailDTO {
    @ApiModelProperty(value = "试听卡ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "课程ID", example = "1001")
    private Long courseId;

    @ApiModelProperty(value = "试听卡标题", example = "英语体验卡")
    private String title;

    @ApiModelProperty(value = "发放数量", example = "100")
    private Integer quantity;

    @ApiModelProperty(value = "剩余数量", example = "80")
    private Integer remainingQuantity;

    @ApiModelProperty(value = "课时数", example = "8")
    private Integer lessonCount;

    @ApiModelProperty(value = "领取后有效天数", example = "30")
    private Integer expireDays;

    @ApiModelProperty(value = "发行结束日期", example = "2026-12-31")
    private LocalDate endDate;

    @ApiModelProperty(value = "启用状态", example = "true")
    private Boolean state;
}
