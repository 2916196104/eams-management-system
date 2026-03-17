package com.zeroone.star.project.query.j3.teachingstats;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;


@Data
public class ClassHourStatsQuery {
    /**
     * 开始日期
     */
    @ApiModelProperty(value = "开始日期", example = "2026-03-16")
    private LocalDate startDate;

    /**
     * 结束日期
     */
    @ApiModelProperty(value = "结束日期", example = "2026-03-18")
    private LocalDate endDate;
}
