package com.zeroone.star.project.vo.j8.stumanager.common;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

/**
 * Points record view object.
 */
@Data
@ApiModel("Points record view object")
public class PointsRecordVO {
    @ApiModelProperty(value = "Record ID", example = "1")
    private Long id;

    @ApiModelProperty(value = "Student ID", example = "1")
    private Long studentId;

    @ApiModelProperty(value = "Student name", example = "Zhang San")
    private String studentName;

    @ApiModelProperty(value = "Points delta", example = "10")
    private Integer credit;

    @ApiModelProperty(value = "Current points", example = "100")
    private Integer currentCredit;

    @ApiModelProperty(value = "Change type", example = "1")
    private Integer changeType;

    @ApiModelProperty(value = "Source ID", example = "3001")
    private Long sourceId;

    @ApiModelProperty(value = "Operator ID", example = "10")
    private Long staffId;

    @ApiModelProperty(value = "Operator name", example = "Li Teacher")
    private String staffName;

    @ApiModelProperty(value = "Change time", example = "2026-03-15T10:00:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "Remark", example = "activity reward")
    private String remark;
}
