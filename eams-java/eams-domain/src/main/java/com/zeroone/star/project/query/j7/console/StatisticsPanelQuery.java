package com.zeroone.star.project.query.j7.console;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：统计面板查询接口声明
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author  不喜欢下雨天（罗涛 j7）
 * @version 1.0.0
 */
@Data
public class StatisticsPanelQuery {
    /**
     * 组织机构ID
     */
    @ApiModelProperty(value = "组织机构ID，非必传")
    private Long orgId;

    /**
     * 统计年份（用于本月报名金额统计，默认当前年）
     */
    @ApiModelProperty(value = "统计年份，默认当前年")
    private Integer year;

    /**
     * 统计月份（用于本月报名金额统计，默认当前月）
     */
    @ApiModelProperty(value = "统计月份，默认当前月")
    private Integer month;
}
