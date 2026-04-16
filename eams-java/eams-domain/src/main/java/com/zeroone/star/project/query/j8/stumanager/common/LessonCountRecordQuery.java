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
 * 消课记录查询参数
 */
@Data
@EqualsAndHashCode(callSuper = true)
@ApiModel("消课记录查询参数")
public class LessonCountRecordQuery extends PageQuery {
    @NotNull(message = "学员ID不能为空")
    @ApiModelProperty(value = "学员ID", example = "1", required = true)
    private Long studentId;

    @ApiModelProperty(value = "课程ID", example = "1001")
    private Long courseId;

    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    @ApiModelProperty(value = "开始时间", example = "2026-03-01 00:00:00")
    private LocalDateTime beginTime;

    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    @ApiModelProperty(value = "结束时间", example = "2026-03-31 23:59:59")
    private LocalDateTime endTime;
}
