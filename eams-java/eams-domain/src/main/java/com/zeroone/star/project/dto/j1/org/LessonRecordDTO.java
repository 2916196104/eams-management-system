package com.zeroone.star.project.dto.j1.org;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.time.LocalDate;
import java.time.LocalTime;


@Data
@ApiModel(value = "授课记录DTO", description = "授课记录列表返回数据")
public class LessonRecordDTO {

    @ApiModelProperty(value = "课次ID", example = "1001")
    private Long id;

    @ApiModelProperty(value = "课程标题", example = "小学数学第一节")
    private String title;

    @ApiModelProperty(value = "第几节课", example = "1")
    private Integer sn;

    // ===================== 上课时间 =====================
    @ApiModelProperty(value = "上课日期", example = "2025-09-10")
    @JsonFormat(pattern = "yyyy-MM-dd",shape = JsonFormat.Shape.STRING)
    private LocalDate date;

    @ApiModelProperty(value = "上课开始时间", example = "08:30:00")
    @JsonFormat(pattern = "HH:mm:ss",shape = JsonFormat.Shape.STRING)
    private LocalTime startTime;

    @ApiModelProperty(value = "上课结束时间", example = "10:00:00")
    @JsonFormat(pattern = "HH:mm:ss",shape = JsonFormat.Shape.STRING)
    private LocalTime endTime;

    // ===================== 所属课程 =====================
    @ApiModelProperty(value = "课程ID", example = "2001")
    private Long courseId;

    @ApiModelProperty(value = "课程名称", example = "三年级数学同步班", required = true)
    private String courseName;

    // ===================== 班级名称 =====================
    @ApiModelProperty(value = "班级ID", example = "3001")
    private Long classId;

    @ApiModelProperty(value = "班级名称", example = "三年级数学一班", required = true)
    private String className;

    // ===================== 教室 =====================
    @ApiModelProperty(value = "教室ID", example = "4001")
    private Long roomId;

    @ApiModelProperty(value = "教室名称", example = "一楼103教室")
    private String classroomName;

    @ApiModelProperty(value = "教室位置", example = "教学楼A座一楼")
    private String classroomAddress;

    // ===================== 上课老师 & 助教 =====================
    @ApiModelProperty(value = "主讲老师ID", example = "5001")
    private Long teacherId;

    @ApiModelProperty(value = "主讲老师姓名", example = "李老师", required = true)
    private String teacherName;

    @ApiModelProperty(value = "助教姓名（多个逗号分隔）", example = "王老师,张老师")
    private String assistantNames;

    // ===================== 状态 & 统计 =====================
    @ApiModelProperty(value = "课次状态 1-未上课 2-已上课 3-已取消", example = "1", required = true)
    private Integer state;

    @ApiModelProperty(value = "状态名称", example = "未上课")
    private String stateName;

    @ApiModelProperty(value = "已取消课数", example = "0")
    private Integer canceledCount;

    @ApiModelProperty(value = "上课情况", example = "正常上课")
    private String lessonStatus;

    @ApiModelProperty(value = "应扣课次数", example = "1")
    private Integer decCount;
}