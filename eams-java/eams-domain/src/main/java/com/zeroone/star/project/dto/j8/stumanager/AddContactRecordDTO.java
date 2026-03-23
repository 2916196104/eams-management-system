package com.zeroone.star.project.dto.j8.stumanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.time.LocalDateTime;

/**
 * 添加跟进记录DTO
 */
@Data
@ApiModel(value = "AddContactRecordDTO", description = "添加跟进记录参数")
public class AddContactRecordDTO {

    @NotNull(message = "学员ID不能为空")
    @ApiModelProperty(value = "学员ID", example = "1", required = true)
    private Long studentId;

    @NotBlank(message = "跟进记录不能为空")
    @ApiModelProperty(value = "跟进记录内容", example = "客户有意向，需要跟进", required = true)
    private String info;

    @NotNull(message = "联系时间不能为空")
    @ApiModelProperty(value = "联系时间", example = "2026-03-21T00:00:00", required = true)
    private LocalDateTime contactTime;

    @ApiModelProperty(value = "下次联系时间", example = "2026-03-21T00:00:00")
    private LocalDateTime contactNextTime;

    @ApiModelProperty(value = "联系方式", example = "1")
    private Integer contactType;

    @ApiModelProperty(value = "联系电话", example = "13800138000")
    private String contactPhone;

    @ApiModelProperty(value = "进展阶段", example = "1")
    private Integer stage;
}
