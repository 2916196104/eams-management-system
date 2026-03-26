package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

/**
 * <p>
 * 描述：本月报名统计视图对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@ApiModel("本月报名统计视图对象")
@Data
public class MonthEnrollmentVO {
    
    @ApiModelProperty(value = "月份", example = "2024-03")
    private String month;
    
    @ApiModelProperty(value = "总报名人数", example = "328")
    private Integer totalEnrollments;
    
    @ApiModelProperty(value = "目标完成率", example = "82.5")
    private Double targetCompletionRate;
    
    @ApiModelProperty(value = "每日报名数据列表", example = "[{'date':'2024-03-01','count':15}]")
    private List<DailyEnrollmentData> dailyData;
    
    /**
     * 每日报名数据内部类
     */
    @Data
    public static class DailyEnrollmentData {
        @ApiModelProperty(value = "日期", example = "2024-03-01")
        private String date;
        
        @ApiModelProperty(value = "报名数量", example = "15")
        private Integer count;
    }
}
