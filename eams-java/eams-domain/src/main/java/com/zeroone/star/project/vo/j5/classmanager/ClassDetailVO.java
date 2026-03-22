package com.zeroone.star.project.vo.j5.classmanager;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
@ApiModel(description = "班级详情VO")
public class ClassDetailVO {

    @ApiModelProperty(value = "主键", example = "1")
    private Long id;


    // 核心ID（用于后续编辑、查询操作）
    @ApiModelProperty(value = "班级ID", example = "1")
    private Long classId;

    // ========== 基本信息展示字段（和截图一一对应） ==========
    @ApiModelProperty(value = "班级名称", example = "钢琴一班")
    private String className;

    @ApiModelProperty(value = "课程名称", example = "钢琴入门课")
    private String courseName;

    @ApiModelProperty(value = "科目名称", example = "钢琴")
    private String subjectName;

    @ApiModelProperty(value = "负责老师（班主任）", example = "管理员")
    private String teacherName;

    @ApiModelProperty(value = "助教姓名", example = "张三")
    private String assistantName;

    @ApiModelProperty(value = "教室名称", example = "多媒体一教")
    private String classroomName;

    @ApiModelProperty(value = "当前学生数", example = "1")
    private Integer currentStudentCount;

    @ApiModelProperty(value = "计划胜（招）生人数", example = "20")
    private Integer plannedStudentCount;

    @ApiModelProperty(value = "计划排课数", example = "5")
    private Integer plannedLessonCount;

    @ApiModelProperty(value = "已上/已排课数", example = "17/17")
    private String lessonProgress;

    @ApiModelProperty(value = "创建时间", example = "2026-01-16")
    private LocalDate createTime;

    @ApiModelProperty(value = "计划开班日期", example = "2026-01-16")
    private LocalDate startDate;

    @ApiModelProperty(value = "计划结业日期", example = "2026-03-28")
    private LocalDate endDate;

    @ApiModelProperty(value = "排课备注", example = "每周一三五上课")
    private String remark;

    @ApiModelProperty(value = "班级状态", example = "进行中")
    private String status;

}

