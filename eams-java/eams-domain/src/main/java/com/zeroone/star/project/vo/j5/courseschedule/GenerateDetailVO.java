package com.zeroone.star.project.vo.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;

/**
 * 生成详情VO
 *
 * @author j5-courseschedule
 * @since 2026-03-17
 */
@Data
@ApiModel(description = "生成详情VO")
public class GenerateDetailVO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "排课计划ID", example = "1001")
    private Long scheduleId;

    @ApiModelProperty(value = "班级名称", example = "Python基础班01期")
    private String className;

    @ApiModelProperty(value = "课程名称", example = "Python编程基础")
    private String courseName;

    @ApiModelProperty(value = "生成的课次数量", example = "15")
    private Integer lessonCount;

    @ApiModelProperty(value = "开始日期", example = "2026-03-20")
    private String startDate;

    @ApiModelProperty(value = "结束日期", example = "2026-06-30")
    private String endDate;

    @ApiModelProperty(value = "生成状态：1-成功 0-失败", example = "1")
    private Integer status;

    @ApiModelProperty(value = "备注信息", example = "已排除3个节假日")
    private String remark;
}
