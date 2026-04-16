package com.zeroone.star.project.dto.j9.course;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.Min;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@ApiModel("课程体验卡数据")
public class CourseTrialDTO {
    @ApiModelProperty(value = "主键ID", example = "1")
    private Long id;

    @NotNull(message = "课程ID不能为空")
    @ApiModelProperty(value = "课程ID", example = "101", required = true)
    private Long courseId;

    @NotBlank(message = "体验卡名称不能为空")
    @ApiModelProperty(value = "体验卡名称", example = "Java基础体验卡", required = true)
    private String title;

    @NotNull(message = "发行数量不能为空")
    @Min(value = 1, message = "发行数量至少为1")
    @ApiModelProperty(value = "发行数量", example = "100", required = true)
    private Integer quantity = 0;

    @ApiModelProperty(value = "剩余数量", example = "50")
    private Integer remainingQuantity;

    @NotNull(message = "课时数不能为空")
    @Min(value = 1, message = "课时数至少为1")
    @ApiModelProperty(value = "课时数", example = "3", required = true)
    private Integer lessonCount = 0;

    @NotNull(message = "有效天数不能为空")
    @ApiModelProperty(value = "领取后有效天数", example = "7", required = true)
    private Integer expireDays;

    @NotNull(message = "发行结束日期不能为空")
    @ApiModelProperty(value = "发行结束日期", example = "2024-12-31", required = true)
    private LocalDate endDate;

    @ApiModelProperty(value = "启用状态: 0-禁用, 1-启用", example = "1")
    private Integer state = 1;

    @ApiModelProperty(value = "创建人ID", example = "1001")
    private Long creator;

    @ApiModelProperty(value = "编辑人ID", example = "1002")
    private Long editor;

    @ApiModelProperty(value = "添加时间", example = "2024-01-15 10:30:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "编辑时间", example = "2024-01-20 14:30:00")
    private LocalDateTime editTime;

    @ApiModelProperty(value = "删除标记: 0-未删除, 1-已删除", example = "0")
    private Integer deleted = 0;

    @ApiModelProperty(value = "创建者所属组织ID", example = "1000")
    private Long orgId;
}
