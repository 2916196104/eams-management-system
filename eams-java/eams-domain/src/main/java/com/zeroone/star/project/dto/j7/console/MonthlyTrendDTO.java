package com.zeroone.star.project.dto.j7.console;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

/**
 * <p>
 * 描述：本月报名走势数据
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 不喜欢下雨天（罗涛 j7）
 * @version 1.0.0
 */
@Data
public class MonthlyTrendDTO {
    @ApiModelProperty(value = "日期", example = "2023-01-01")
    private String date;         // 日期

    @ApiModelProperty(value = "总报名次数")
    private Integer totalCount;     // 总报名次数
}
