package com.zeroone.star.project.vo.j9.operation;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.Date;

/**
 * 描述：试听卡视图对象
 * @author paopao
 * @version 1.0.0
 */
@Data
@ApiModel("试听卡视图对象")
public class CourseTrialVO {

    @ApiModelProperty(value = "试听卡ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "课程ID", example = "1")
    private Long courseId;

    @ApiModelProperty(value = "试听卡名称", example = "暑期试听卡")
    private String title;

    @ApiModelProperty(value = "发放数量", example = "100")
    private Integer quantity;

    @ApiModelProperty(value = "剩余数量", example = "80")
    private Integer remainingQuantity;

    @ApiModelProperty(value = "课时数", example = "2")
    private Integer lessonCount;

    @ApiModelProperty(value = "领取后有效天数", example = "30")
    private Integer expireDays;

    @ApiModelProperty(value = "发放结束日期", example = "2026-12-31")
    @JsonFormat(pattern = "yyyy-MM-dd")
    private Date endDate;

    @ApiModelProperty(value = "启用状态 1-启用 0-禁用", example = "1")
    private Integer state;

    @ApiModelProperty(value = "创建时间", example = "2026-01-01 00:00:00")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private Date addTime;
}
