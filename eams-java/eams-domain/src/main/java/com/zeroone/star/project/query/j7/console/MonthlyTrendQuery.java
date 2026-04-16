package com.zeroone.star.project.query.j7.console;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;

/**
 * <p>
 * 描述：本月报名走势查询接口声明
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author  不喜欢下雨天（罗涛 j7）
 * @version 1.0.0
 */
@Data
public class MonthlyTrendQuery {
    /**
     * 组织机构ID
     */
    @ApiModelProperty(value = "组织机构ID，非必传")
    private Long orgId;

    /**
     * 开始日期
     */
    @ApiModelProperty(value = "开始日期，默认本月第一天")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;

    /**
     * 结束日期
     */
    @ApiModelProperty(value = "结束日期，默认本月最后一天")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate endDate;
}
