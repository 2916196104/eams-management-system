package com.zeroone.star.project.query.j5.appoint;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import javax.validation.constraints.Size;
import java.time.LocalDate;
import java.util.List;

/**
 * <p>
 * 预约列查询条件对象
 * </p>
 *
 * @author makise
 * @since 2026/3/23
 */
@Data
public class AppointmentQuery extends PageQuery {

    @ApiModelProperty(value = "学生ID列表(支持多选)", example = "[1, 2, 3]")
    @Size(max = 5, message = "一次最多只能查询5个学生")
    private List<Long> studentIds;

    @ApiModelProperty(value = "课程ID列表(支持多选)", example = "[10, 20]")
    @Size(max = 5, message = "一次最多只能查询5门课程")
    private List<Long> courseIds;

    @ApiModelProperty(value = "开始日期", example = "2026-03-01")
    @JsonFormat(pattern = "yyyy-MM-dd")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;

    @ApiModelProperty(value = "结束日期", example = "2026-03-15")
    @JsonFormat(pattern = "yyyy-MM-dd")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate endDate;
}
