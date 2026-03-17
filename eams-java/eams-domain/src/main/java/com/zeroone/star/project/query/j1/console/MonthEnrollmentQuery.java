package com.zeroone.star.project.query.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * <p>
 * 描述：本月报名统计查询对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("本月报名统计查询对象")
@Data
@AllArgsConstructor
@NoArgsConstructor
public class MonthEnrollmentQuery {
    
    /**
     * 年份
     */
    @ApiModelProperty(value = "年份", example = "2024")
    private Integer year;
    
    /**
     * 月份
     */
    @ApiModelProperty(value = "月份", example = "3")
    private Integer month;
    
    /**
     * 课程 ID（可选）
     */
    @ApiModelProperty(value = "课程 ID（可选）", example = "1001")
    private Integer courseId;
}
