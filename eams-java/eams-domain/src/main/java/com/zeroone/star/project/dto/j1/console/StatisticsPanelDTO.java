package com.zeroone.star.project.dto.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.math.BigDecimal;

/**
 * <p>
 * 描述：控制台统计面板数据传输对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@ApiModel("控制台统计面板数据对象")
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
public class StatisticsPanelDTO {
    
    /**
     * 总学员数
     */
    @ApiModelProperty(value = "总学员数", example = "1000")
    private Integer totalStudents;
    
    /**
     * 总教师数
     */
    @ApiModelProperty(value = "总教师数", example = "50")
    private Integer totalTeachers;
    
    /**
     * 总课程数
     */
    @ApiModelProperty(value = "总课程数", example = "120")
    private Integer totalCourses;
    
    /**
     * 总班级数
     */
    @ApiModelProperty(value = "总班级数", example = "30")
    private Integer totalClasses;
    
    /**
     * 今日出勤率（百分比）
     */
    @ApiModelProperty(value = "今日出勤率", example = "95.5")
    private BigDecimal todayAttendanceRate;
    
    /**
     * 本月新增学员数
     */
    @ApiModelProperty(value = "本月新增学员数", example = "80")
    private Integer monthNewStudents;
    
    /**
     * 待办事项数量
     */
    @ApiModelProperty(value = "待办事项数量", example = "15")
    private Integer pendingTasks;
    
    /**
     * 系统消息数量
     */
    @ApiModelProperty(value = "系统消息数量", example = "5")
    private Integer systemMessages;
}
