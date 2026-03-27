package com.zeroone.star.project.vo.j1.console;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

/**
 * <p>
 * 描述：课表日历视图对象
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author 康康舞曲
 * @version 1.0.0
 */
@ApiModel("课表日历视图对象")
@Data
public class ScheduleCalendarVO {

    @ApiModelProperty(value = "课次ID", example = "5001")
    private Long id;

    @ApiModelProperty(value = "上课时间", example = "2024-03-18 09:00")
    private String classTime;

    @ApiModelProperty(value = "课程名称", example = "Java高级编程")
    private String courseName;

    @ApiModelProperty(value = "班级名称", example = "Java班1期")
    private String className;

    @ApiModelProperty(value = "上课老师", example = "张老师")
    private String teacherName;

    @ApiModelProperty(value = "类型（授课方式）", example = "1")
    private Integer teachType;

    @ApiModelProperty(value = "助教", example = "李助教")
    private String assistantName;

    @ApiModelProperty(value = "教室", example = "A301")
    private String classroomName;

    @ApiModelProperty(value = "可预约学生数", example = "5")
    private Integer bookableCount;

    @ApiModelProperty(value = "学生数", example = "30")
    private Integer studentCount;

    @ApiModelProperty(value = "签到数", example = "28")
    private Integer signCount;

    @ApiModelProperty(value = "到课率", example = "93.33")
    private BigDecimal attendanceRate;

    @ApiModelProperty(value = "消课基数", example = "1")
    private Integer decCount;

    @ApiModelProperty(value = "状态（1-未开始 2-进行中 3-已结束）", example = "1")
    private Integer state;
}
