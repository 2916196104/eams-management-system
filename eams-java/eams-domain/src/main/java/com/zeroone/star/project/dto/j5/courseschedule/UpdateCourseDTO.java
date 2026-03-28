package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;

@Data
public class UpdateCourseDTO {
    @ApiModelProperty(value = "课程ID", required = true)
    private Long id;

    @ApiModelProperty(value = "课程标题",required = false)
    private String title;

    @ApiModelProperty(value = "班级名",required = false)
    private String className;
    @ApiModelProperty(value = "教师id",required = false)
    private Long classId;

    @ApiModelProperty(value = "教师姓名",required = false)
    private String teacherName;
    @ApiModelProperty(value = "教师id",required = false)
    private Long teacherId;

    @ApiModelProperty(value = "助教姓名",required = false)
    private String assistantName;
    @ApiModelProperty(value = "助教id",required = false)
    private Long assistantId;


    @ApiModelProperty(value = "开始时间", example = "2026-01-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;

    @ApiModelProperty(value = "结束时间", example = "2026-04-01")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate endDate;

    @ApiModelProperty(value = "教室id",required = false)
    private Long roomId;
    @ApiModelProperty(value = "教室名称",required = false)
    private String roomName;

    @ApiModelProperty(value = "消课基数",required = false)
    private Integer decCount;


    @ApiModelProperty(value = "是否开启预约", example = "true")
    private Boolean enableReserve;

    @ApiModelProperty(value = "是否批量同步后续相同时间课程", example = "false",
            notes = "开启后，本班级后续相同时间的课程，将会同步调整；只修改上课时间和老师")
    private Boolean batchSyncTime;

    @ApiModelProperty(value = "是否检查排课冲突", example = "false")
    private Boolean checkConflict;

}
