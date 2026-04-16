package com.zeroone.star.project.vo.j7.operation;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * 试听卡数据显示对象
 */
@Data
@ApiModel("试听卡列表显示对象")
public class TrialCardVO {
    @ApiModelProperty("试听卡ID")
    private Long id;

    @ApiModelProperty("试听卡名称")
    private String title;

    @ApiModelProperty("课程ID")
    private Long courseId;

    @ApiModelProperty("所属课程名称")
    private String courseName;

    @ApiModelProperty("包含课时数")
    private Integer lessonCount;

    @ApiModelProperty("发行数量")
    private Integer quantity;

    @ApiModelProperty("已领取数量")
    private Integer recordCount;

    @ApiModelProperty("领取后有效天数")
    private Integer expireDays;

    @ApiModelProperty("发行结束日期")
    private LocalDate endDate;

    @ApiModelProperty("是否启用")
    private Boolean state;

    @ApiModelProperty("编辑时间")
    private LocalDateTime editTime;

    @ApiModelProperty("编辑人名称")
    private String editorName;
}