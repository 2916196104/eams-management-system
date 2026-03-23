package com.zeroone.star.project.vo.j5.appoint;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
/**
 * <p>
 * 预约课程详情信息弹窗 VO
 * </p>
 *
 * @author makise
 * @since 2026/3/23
 */
@Data
@ApiModel(value = "AppointmentDetailVO", description = "课程详情弹窗信息")
public class AppointmentDetailVO {

    @ApiModelProperty(value = "标题", example = "钢琴入门课")
    private String title;

    @ApiModelProperty(value = "课程名称", example = "钢琴入门课")
    private String courseName;

    @ApiModelProperty(value = "班级名称", example = "钢琴一班")
    private String className;

    @ApiModelProperty(value = "类型(如：小班课)", example = "小班课")
    private String courseType;

    @ApiModelProperty(value = "上课时间展示文本", example = "2026-01-19(一) 11:00 ~ 12:30")
    private String lessonTimeText;

    @ApiModelProperty(value = "教室", example = "多媒体一教")
    private String classroomName;

    @ApiModelProperty(value = "老师", example = "管理员")
    private String teacherName;

    @ApiModelProperty(value = "助教", example = "王老师")
    private String assistantName;

    @ApiModelProperty(value = "实到人数", example = "0")
    private Integer actualAttendance;

    @ApiModelProperty(value = "应到人数", example = "2")
    private Integer expectedAttendance;

    @ApiModelProperty(value = "消课基数", example = "1")
    private Integer deductionBase;

    @ApiModelProperty(value = "是否可预约(1-是, 0-否)", example = "1")
    private Integer isBookable;

    @ApiModelProperty(value = "状态(如：已结课)", example = "已结课")
    private String statusText;
}