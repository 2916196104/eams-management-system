package com.zeroone.star.project.query.j3.data;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;


@Data
public class ClassHourStatsQuery extends PageQuery {
    /**
     * 开始日期
     */
    @ApiModelProperty(value = "开始日期", example = "2026-03-16")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;

    /**
     * 结束日期
     */
    @ApiModelProperty(value = "结束日期", example = "2026-03-18")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate endDate;
}
