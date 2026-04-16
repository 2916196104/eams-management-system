package com.zeroone.star.project.dto.j7.operation;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.Min;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.time.LocalDate;


/**
 * <p>
 * 描述：试听卡
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 1
 * @version 1.0.0
 */

@Data
public class DemoCardDTO {
    @NotNull(message = "ID不能为空")
    @ApiModelProperty(value = "试听卡ID（必填）", required = true)
    private Long id;

    @NotBlank(message = "试听卡名称不能为空")
    @ApiModelProperty(value = "试听卡名称", required = true, example = "钢琴入门试听卡")
    private String name;

    @NotNull(message = "课程ID不能为空")
    @ApiModelProperty(value = "所属课程ID", required = true, example = "3001")
    private Long courseId;

    @Min(value = 1, message = "发行数量至少为1")
    @ApiModelProperty(value = "发行数量", required = true, example = "99")
    private Integer totalIssue;

    @Min(value = 1, message = "课时数至少为1")
    @ApiModelProperty(value = "包含课时数", required = true, example = "5")
    private Integer lessonCount;

    @Min(value = 1, message = "有效天数至少为1")
    @ApiModelProperty(value = "有效天数", required = true, example = "10")
    private Integer validDays;

    @ApiModelProperty(value = "发行结束日期（格式：yyyy-MM-dd）", example = "2026-01-31")
    private LocalDate endDate;

    @ApiModelProperty(value = "是否启用：true-是，false-否", example = "true")
    private Boolean isActive;


}
