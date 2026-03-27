package com.zeroone.star.project.dto.j1.org;


import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

/**
 * <p>
 * 描述：管理员数据传输对象
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author chichu
 * @version 1.0.0
 */
@Data
    @ApiModel(value = "ClassRecordDTO", description = "所代班级列表返回数据")
    public class ClassRecordDTO {

        @ApiModelProperty(value = "班级ID", example = "1001")
        private Long classId;

        // ===================== 你要的核心字段 =====================
        @ApiModelProperty(value = "班级名称", example = "三年级数学一班", required = true)
        private String className;

        @ApiModelProperty(value = "课程名称", example = "三年级数学同步提升班", required = true)
        private String courseName;

        @ApiModelProperty(value = "科目名称", example = "数学", required = true)
        private String subjectName;

        @ApiModelProperty(value = "教室名称", example = "一楼103教室")
        private String classroomName;

        @ApiModelProperty(value = "班主任/班级负责人", example = "李老师")
        private String teacherName;

        @ApiModelProperty(value = "当前学生人数", example = "25")
        private Integer studentCount;

        @ApiModelProperty(value = "预招人数", example = "30")
        private Integer plannedStudentCount;

        @ApiModelProperty(value = "计划课次总数", example = "40")
        private Integer plannedLessonCount;

        @ApiModelProperty(value = "已排课次数", example = "15")
        private Integer scheduledLessonCount;

        @ApiModelProperty(value = "已上课次数", example = "10")
        private Integer finishedLessonCount;

        @ApiModelProperty(value = "上课进度 百分比", example = "25%")
        private String lessonProgress;

        @ApiModelProperty(value = "排课备注", example = "每周一、三、五晚上课")
        private String remark;

        @ApiModelProperty(value = "计划开班日期", example = "2025-09-01")
        @JsonFormat(pattern = "yyyy-MM-dd",shape = JsonFormat.Shape.STRING)
        private LocalDate startDate;

        @ApiModelProperty(value = "计划结业日期", example = "2026-01-10")
        @JsonFormat(pattern = "yyyy-MM-dd",shape = JsonFormat.Shape.STRING)
        private LocalDate endDate;

        @ApiModelProperty(value = "班级状态 0-未开班 1-正常 2-已完结", example = "1")
        private Integer classStatus;

        @ApiModelProperty(value = "状态名称", example = "正常")
        private String statusName;

        // ===================== 辅助字段 =====================
        @ApiModelProperty(value = "课程ID", example = "2001")
        private Long courseId;

        @ApiModelProperty(value = "是否完结 0-否 1-是", example = "0")
        private Integer beOver;
    }

