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
 * @author 阿伟学长
 * @version 1.0.0
 */
@ApiModel("控制台统计面板视图对象")
@Data
public class ConsoleStatisticsVO {
    @ApiModelProperty(value = "学生总数", example = "1200")
    private Integer totalStudents;

    @ApiModelProperty(value = "教师总数", example = "85")
    private Integer totalTeachers;

    @ApiModelProperty(value = "课程总数", example = "156")
    private Integer totalCourses;

    @ApiModelProperty(value = "班级总数", example = "42")
    private Integer totalClasses;

    @ApiModelProperty(value = "今日出勤率", example = "96.5")
    private Double todayAttendanceRate;

    @ApiModelProperty(value = "本月报名数", example = "328")
    private Integer monthEnrollments;

    @ApiModelProperty(value = "待处理事项数量", example = "15")
    private Integer pendingTasks;
}
