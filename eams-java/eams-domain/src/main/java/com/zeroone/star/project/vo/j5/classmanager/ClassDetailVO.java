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

    @ApiModelProperty(value = "班级名", example = "三年二班")
    private String name;

    @ApiModelProperty(value = "课程ID", example = "5")
    private Long courseId;

    @ApiModelProperty(value = "课程名称", example = "数学")
    private String courseName;

    @ApiModelProperty(value = "教室ID", example = "10")
    private Long classroomId;

    @ApiModelProperty(value = "教室名称", example = "A101")
    private String classroomName;

    @ApiModelProperty(value = "班级负责人ID", example = "3")
    private Long teacherId;

    @ApiModelProperty(value = "班主任姓名", example = "张老师")
    private String teacherName;

    @ApiModelProperty(value = "年级ID", example = "2")
    private Integer gradeId;

    @ApiModelProperty(value = "年级名称", example = "三年级")
    private String gradeName;

    @ApiModelProperty(value = "排课备注", example = "数学强化班")
    private String remark;

    @ApiModelProperty(value = "是否完结", example = "false")
    private Boolean beOver;

    @ApiModelProperty(value = "完结时间", example = "2023-06-30 18:00:00")
    private LocalDateTime overTime;

    @ApiModelProperty(value = "计划开班日期", example = "2023-03-01")
    private LocalDate startDate;

    @ApiModelProperty(value = "计划结业日期", example = "2023-07-01")
    private LocalDate endDate;

    @ApiModelProperty(value = "预招人数", example = "30")
    private Integer plannedStudentCount;

    @ApiModelProperty(value = "预排课次数", example = "20")
    private Integer plannedLessonCount;

    @ApiModelProperty(value = "创建者所属学校id", example = "100")
    private Long schoolId;

    @ApiModelProperty(value = "创建者所属组织ID", example = "200")
    private Long orgId;

    @ApiModelProperty(value = "添加时间", example = "2023-01-01 10:00:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "编辑时间", example = "2023-01-02 11:00:00")
    private LocalDateTime editTime;
}

