package com.zeroone.star.project.dto.j9.operation;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import javax.validation.constraints.Min;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.util.Date;

/**
 * 描述：试听卡数据传输对象（新增传id为空，修改传id）
 * @author paopao
 * @version 1.0.0
 */
@Data
@ApiModel("试听卡数据传输对象")
public class CourseTrialDTO {

    @ApiModelProperty(value = "试听卡ID（修改时必传，新增时不传）", example = "1")
    private Long id;

    @ApiModelProperty(value = "课程ID", example = "1", required = true)
    @NotNull(message = "课程ID不能为空")
    private Long courseId;

    @ApiModelProperty(value = "试听卡名称", example = "暑期试听卡", required = true)
    @NotBlank(message = "试听卡名称不能为空")
    private String title;

    @ApiModelProperty(value = "发放数量", example = "100", required = true)
    @NotNull(message = "发放数量不能为空")
    @Min(value = 1, message = "发放数量至少为1")
    private Integer quantity;

    @ApiModelProperty(value = "课时数", example = "2", required = true)
    @NotNull(message = "课时数不能为空")
    @Min(value = 1, message = "课时数至少为1")
    private Integer lessonCount;

    @ApiModelProperty(value = "领取后有效天数", example = "30", required = true)
    @NotNull(message = "有效天数不能为空")
    @Min(value = 1, message = "有效天数至少为1")
    private Integer expireDays;

    @ApiModelProperty(value = "发放结束日期", example = "2026-12-31", required = true)
    @NotNull(message = "发放结束日期不能为空")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    @JsonFormat(pattern = "yyyy-MM-dd")
    private Date endDate;

    @ApiModelProperty(value = "启用状态 1-启用 0-禁用", example = "1")
    private Integer state;
}
