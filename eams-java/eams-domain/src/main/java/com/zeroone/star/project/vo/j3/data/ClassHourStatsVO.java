package com.zeroone.star.project.vo.j3.data;


import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;

@Data
public class ClassHourStatsVO {
    @ApiModelProperty(value = "老师姓名", example = "刘")
    private String teacherName;

    @ApiModelProperty(value = "总课时数", example = "100")
    private Double totalHours;

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
