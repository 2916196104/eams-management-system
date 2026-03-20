package com.zeroone.star.project.query.j5.courseschedule;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;
import java.util.List;

@Data
public class UpdateCoursesQuery {
    @ApiModelProperty(value = "课程ID列表", required = true, example = "1,2,3")
    private List<Long> courseIds;

    @ApiModelProperty(value = "课次状态", required = true, example = "1")
    private Integer status;

    @ApiModelProperty(value = "增减天数", required = false, example = "1")
    private String weeks;

    @ApiModelProperty(value = "开始时间", example = "2026-01-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;

    @ApiModelProperty(value = "结束时间", example = "2026-04-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate endDate;

    @ApiModelProperty(value = "教室ID", required = false, example = "1")
    private Long roomId;

    @ApiModelProperty(value = "教师ID", required = false, example = "1")
    private Long teacherId;

    @ApiModelProperty(value = "老师和助教的转换", required = false)
    private Long typeNum;
}
