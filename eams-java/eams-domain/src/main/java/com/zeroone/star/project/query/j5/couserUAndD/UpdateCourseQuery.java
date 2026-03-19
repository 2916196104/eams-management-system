package com.zeroone.star.project.query.j5.couserUAndD;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;

@Data
public class UpdateCourseQuery {
    @ApiModelProperty(value = "课程ID", required = true)
    private Long id;

    @ApiModelProperty(value = "课程标题",required = false)
    private String title;

    @ApiModelProperty(value = "老分校id",required = false)
    private Long schoolId;

    @ApiModelProperty(value = "课程id",required = false)
    private Long courseId;

    @ApiModelProperty(value = "教师id",required = false)
    private Long teacherId;

    @ApiModelProperty(value = "上课时间", example = "2026-01-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate date;

    @ApiModelProperty(value = "开始时间", example = "2026-01-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;

    @ApiModelProperty(value = "结束时间", example = "2026-04-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate endDate;

    @ApiModelProperty(value = "教室id",required = false)
    private Long roomId;

    @ApiModelProperty(value = "消课基数",required = false)
    private Integer decCount;

    @ApiModelProperty(value = "是否可预约",required = false)
    private Integer bookable;

    @ApiModelProperty(value = "是否检查冲突",required = false)
    private String conflictIds;
}
