package com.zeroone.star.project.vo.j7.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

@Data
@ApiModel("试听卡详情显示对象")
public class TrialCardDetailVO {
    @ApiModelProperty("试听卡ID")
    private Long id;

    @ApiModelProperty("试听卡名称")
    private String title;

    @ApiModelProperty("课程ID (用于下拉框选中)")
    private Long courseId;

    @ApiModelProperty("课程名称 (用于显示)")
    private String courseName;

    @ApiModelProperty("发行数量")
    private Integer quantity;

    @ApiModelProperty("包含课时数")
    private Integer lessonCount;

    @ApiModelProperty("领取后有效天数")
    private Integer expireDays;

    @ApiModelProperty("发行结束日期")
    private LocalDate endDate;

    @ApiModelProperty("是否启用")
    private Boolean state;
}
