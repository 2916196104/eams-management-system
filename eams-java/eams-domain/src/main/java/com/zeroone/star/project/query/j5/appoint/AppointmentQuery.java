package com.zeroone.star.project.query.j5.appoint;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;
import java.util.List;

/**
 * 预约查询对象
 */
@Data
public class AppointmentQuery extends PageQuery {

    @ApiModelProperty(value = "学生名称列表(支持多选)", example = "[张三, 李四, 小名]")
    private List<String> studentNames;

    @ApiModelProperty(value = "课程名称列表(支持多选)", example = "[英文, 数学]")
    private List<String> courseNames;

    @ApiModelProperty(value = "开始日期", example = "2026-03-01")
    @JsonFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;

    @ApiModelProperty(value = "结束日期", example = "2026-03-15")
    @JsonFormat(pattern = "yyyy-MM-dd")
    private LocalDate endDate;
}
