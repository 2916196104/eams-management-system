package com.zeroone.star.project.dto.j7.console;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

/**
 * <p>
 * 描述：统计面板核心指标
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 不喜欢下雨天（罗涛 j7）
 * @version 1.0.0
 */
@Data
public class StatisticsPanelDTO {
    @ApiModelProperty(value = "学员人数")
    private Long studentCount;          // 学员人数
    @ApiModelProperty(value = "师资人数")
    private Long teacherCount;          // 师资人数
    @ApiModelProperty(value = "总课次")
    private Long totalLessonCount;      // 总课次
    @ApiModelProperty(value = "本月报名金额")
    private BigDecimal monthlyRevenue;  // 本月报名金额
}
