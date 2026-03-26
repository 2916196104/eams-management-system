package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * <p>
 * 描述：控制台统计面板视图对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@ApiModel("控制台统计面板视图对象")
@Data
public class ConsoleStatisticsVO {
    
    @ApiModelProperty(value = "学员数", example = "1200")
    private Integer totalStudents;
    
    @ApiModelProperty(value = "总课次", example = "27")
    private Integer totalLessons;
    
    @ApiModelProperty(value = "师资人数", example = "85")
    private Integer totalTeachers;
    
    @ApiModelProperty(value = "本月报名(万元)", example = "128.5")
    private Double monthEnrollmentAmount;
}
