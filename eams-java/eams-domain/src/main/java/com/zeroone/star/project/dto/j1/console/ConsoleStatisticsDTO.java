package com.zeroone.star.project.dto.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * <p>
 * 描述：控制台统计面板数据对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("控制台统计面板数据对象")
@Data
@AllArgsConstructor
@NoArgsConstructor
public class ConsoleStatisticsDTO {
    
    /**
     * 学生总数
     */
    @ApiModelProperty(value = "学生总数", example = "1200")
    private Integer totalStudents;
    
    /**
     * 教师总数
     */
    @ApiModelProperty(value = "教师总数", example = "85")
    private Integer totalTeachers;
    
    /**
     * 课程总数
     */
    @ApiModelProperty(value = "课程总数", example = "156")
    private Integer totalCourses;
    
    /**
     * 班级总数
     */
    @ApiModelProperty(value = "班级总数", example = "42")
    private Integer totalClasses;
    
    /**
     * 今日出勤率（百分比）
     */
    @ApiModelProperty(value = "今日出勤率", example = "96.5")
    private Double todayAttendanceRate;
    
    /**
     * 本月报名数
     */
    @ApiModelProperty(value = "本月报名数", example = "328")
    private Integer monthEnrollments;
    
    /**
     * 待处理事项数量
     */
    @ApiModelProperty(value = "待处理事项数量", example = "15")
    private Integer pendingTasks;
}
