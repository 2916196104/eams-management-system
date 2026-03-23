package com.zeroone.star.project.query.j8.stumanager.common;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import lombok.EqualsAndHashCode;
import org.springframework.format.annotation.DateTimeFormat;

import javax.validation.constraints.NotNull;
import java.time.LocalDateTime;

/**
 * Points record query.
 */
@Data
@EqualsAndHashCode(callSuper = true)
@ApiModel("Points record query")
public class PointsRecordQuery extends PageQuery {
    @NotNull(message = "studentId cannot be null")
    @ApiModelProperty(value = "Student ID", example = "1", required = true)
    private Long studentId;

    @ApiModelProperty(value = "Change type", example = "1")
    private Integer changeType;

    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    @ApiModelProperty(value = "Begin time", example = "2026-03-01 00:00:00")
    private LocalDateTime beginTime;

    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    @ApiModelProperty(value = "End time", example = "2026-03-31 23:59:59")
    private LocalDateTime endTime;
}
