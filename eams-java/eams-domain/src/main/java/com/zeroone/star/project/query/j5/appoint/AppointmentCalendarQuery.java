package com.zeroone.star.project.query.j5.appoint;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.format.annotation.DateTimeFormat;

import javax.validation.constraints.NotNull;
import java.io.Serializable;
import java.time.LocalDate;

/**
 * <p>
 * 描述：预约日历查询参数
 * </p>
 *
 * @author : 小可
 * @date : 2026/3/15 16:16
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
@ApiModel("预约日历查询参数")
public class AppointmentCalendarQuery implements Serializable {

    @ApiModelProperty(value = "开始时间", example = "2026-02-23")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    @NotNull(message = "开始时间不能为空")
    private LocalDate startDate;

    @ApiModelProperty(value = "结束时间", example = "2026-04-05")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    @NotNull(message = "结束时间不能为空")
    private LocalDate endDate;

}
