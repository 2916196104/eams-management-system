package com.zeroone.star.project.query.j8.stumanager;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

/**
 * 跟进记录查询参数
 */
@Data
@ApiModel(description = "跟进记录查询参数")
public class ContactRecordQuery extends PageQuery {

    @ApiModelProperty(value = "学员ID", example = "1")
    private Long studentId;

    @ApiModelProperty(value = "跟进人ID", example = "1")
    private Long creator;

    @ApiModelProperty(value = "跟进开始日期", example = "2026-01-01")
    private LocalDate startDate;

    @ApiModelProperty(value = "跟进结束日期", example = "2026-12-31")
    private LocalDate endDate;

    @ApiModelProperty(value = "进展阶段", example = "1")
    private Integer stage;
}
