package com.zeroone.star.project.vo.j5.appoint;

import com.fasterxml.jackson.annotation.JsonIgnore;
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

    @ApiModelProperty(value = "课程ID", example = "1001")
    private Long courseId;

    @ApiModelProperty(value = "班级名称", example = "钢琴一班")
    private String className;

    @ApiModelProperty(value = "班级ID", example = "2001")
    private Long classId;


    @ApiModelProperty(value = "类型(如：小班课)", example = "小班课")
    private String courseType;

    @ApiModelProperty(value = "上课时间展示文本", example = "2026-01-19(一) 11:00 ~ 12:30")
    private String lessonTimeText;

    @ApiModelProperty(value = "教室", example = "多媒体一教")
    private String classroomName;

    @ApiModelProperty(value = "老师", example = "管理员")
    private String teacherName;


    @ApiModelProperty(value = "教师ID", example = "3001")
    private Long teacherId;

    @ApiModelProperty(value = "助教", example = "王老师")
    private String assistantName;

    @ApiModelProperty(value = "助教ID", example = "4001")
    private Long assistantId;
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

    // ---------------- 以下为后端处理数据所需的隐藏字段 ----------------

    @JsonIgnore // 查出来但不返回给前端JSON
    @ApiModelProperty(hidden = true)
    private java.time.LocalDate rawDate;

    @JsonIgnore
    @ApiModelProperty(hidden = true)
    private java.time.LocalTime rawStartTime;

    @JsonIgnore
    @ApiModelProperty(hidden = true)
    private java.time.LocalTime rawEndTime;

    @JsonIgnore
    @ApiModelProperty(hidden = true)
    private Integer rawCourseType; // 接收 course_type 的数字值

    @JsonIgnore
    @ApiModelProperty(hidden = true)
    private Integer rawState; // 接收 lesson_state 的数字值
}