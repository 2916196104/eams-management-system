package com.zeroone.star.project.vo.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;
import java.util.List;

/**
 * 删除课表响应VO
 *
 * @author j5-courseschedule
 * @since 2026-03-17
 */
@ApiModel(description = "删除课表响应VO")
@Data
public class DeleteLessonResultVO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "处理的排课计划总数", example = "3")
    private Integer totalCount;

    @ApiModelProperty(value = "成功删除的排课计划数量", example = "3")
    private Integer successCount;

    @ApiModelProperty(value = "删除的课次总数", example = "45")
    private Integer lessonCount;

    @ApiModelProperty(value = "删除失败的排课计划ID列表", example = "[]")
    private List<Long> failedList;

    @ApiModelProperty(value = "失败详情列表")
    private List<FailedDetailVO> failedDetails;
}
