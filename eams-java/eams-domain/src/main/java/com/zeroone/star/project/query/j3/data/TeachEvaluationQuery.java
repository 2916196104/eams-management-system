package com.zeroone.star.project.query.j3.data;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;


/**
 * 学评教统计查询条件对象
 */
@Data
public class TeachEvaluationQuery extends PageQuery {
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

    /**
     * 排序字段
     */
    @ApiModelProperty(value = "排序字段", example = "evaluationCount")
    private String sortBy;

    /**
     * 排序方式: "asc" (升序) 或 "desc" (降序),  默认为desc
     */
    @ApiModelProperty(value = "排序方式: asc或desc,  默认为desc", example = "desc")
    private String sortOrder = "desc";

}