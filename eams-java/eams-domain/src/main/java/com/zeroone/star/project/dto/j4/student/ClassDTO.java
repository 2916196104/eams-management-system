package com.zeroone.star.project.dto.j4.student;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：班级信息传输对象
 */
@Data
public class ClassDTO {

    @ApiModelProperty(value = "班级ID，修改时必传，新增不传", example = "2008418408985583620")
    private Long id;

    @ApiModelProperty(value = "班级名", required = true, example = "2026届Java高端就业班")
    private String name;

    @ApiModelProperty(value = "课程ID", required = true, example = "1001")
    private Long courseId;

    @ApiModelProperty(value = "教室ID", example = "305")
    private Long classroomId;

    @ApiModelProperty(value = "班级负责人/教师ID", required = true, example = "2001")
    private Long teacherId;

    @ApiModelProperty(value = "排课备注", example = "周末上课，注意安排")
    private String remark;

    @ApiModelProperty(value = "年级ID", example = "2023")
    private Integer gradeId;

    @ApiModelProperty(value = "预招人数", example = "50")
    private Integer plannedStudentCount;

    @ApiModelProperty(value = "预排课次数", example = "120")
    private Integer plannedLessonCount;

    @ApiModelProperty(value = "计划开班日期", example = "2026-04-01")
    @JsonFormat(pattern = "yyyy-MM-dd", timezone = "GMT+8")
    private LocalDate startDate;

    @ApiModelProperty(value = "计划结业日期", example = "2026-09-30")
    @JsonFormat(pattern = "yyyy-MM-dd", timezone = "GMT+8")
    private LocalDate endDate;

    @ApiModelProperty(value = "创建者所属学校id", example = "500")
    private Long schoolId;

    @ApiModelProperty(value = "创建者所属组织ID", example = "10")
    private Long orgId;

    // 以下字段通常为系统自动填充或只读，视业务需求决定是否在DTO中暴露
    @ApiModelProperty(value = "是否完结 (0:否 1:是)", example = "0")
    private Integer beOver;

    @ApiModelProperty(value = "完结时间", example = "2026-09-30 17:00:00")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private LocalDateTime overTime;

    @ApiModelProperty(value = "添加时间", example = "2026-03-16 10:00:00")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private LocalDateTime addTime;
}