package com.zeroone.star.project.vo.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * 排课计划VO
 *
 * @author j5-courseschedule
 * @since 2026-03-17
 */
@Data
@ApiModel(description = "排课计划VO")
public class LessonScheduleVO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "主键", example = "1001")
    private Long id;

    @ApiModelProperty(value = "班级ID", example = "2001")
    private Long classId;

    @ApiModelProperty(value = "班级名称", example = "Python基础班01期")
    private String className;

    @ApiModelProperty(value = "课程ID", example = "3001")
    private Long courseId;

    @ApiModelProperty(value = "课程名称", example = "Python编程基础")
    private String courseName;

    @ApiModelProperty(value = "上课老师ID列表（逗号分隔）", example = "101,102")
    private String teacherIds;

    @ApiModelProperty(value = "上课老师名称列表", example = "张老师,李老师")
    private String teacherNames;

    @ApiModelProperty(value = "助教ID列表（逗号分隔）", example = "201")
    private String assistantIds;

    @ApiModelProperty(value = "助教名称列表", example = "王助教")
    private String assistantNames;

    @ApiModelProperty(value = "开始日期", example = "2026-03-20")
    private LocalDate startDate;

    @ApiModelProperty(value = "结束日期", example = "2026-06-30")
    private LocalDate endDate;

    @ApiModelProperty(value = "学员扣课次数", example = "1")
    private Integer decLessonCount;

    @ApiModelProperty(value = "排课次数", example = "15")
    private Integer times;

    @ApiModelProperty(value = "是否排除节日：0-否 1-是", example = "1")
    private Integer excludeHoliday;

    @ApiModelProperty(value = "是否生成课表：0-未生成 1-已生成", example = "0")
    private Integer state;

    @ApiModelProperty(value = "冲突的id列表（空字符表示无冲突，null表示未检查）", example = "")
    private String conflictIds;

    @ApiModelProperty(value = "创建时间", example = "2026-03-17T10:30:00")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "创建人ID", example = "1")
    private Long creator;

    @ApiModelProperty(value = "创建人名称", example = "管理员")
    private String creatorName;

    @ApiModelProperty(value = "组织ID", example = "100")
    private Long orgId;

    @ApiModelProperty(value = "组织名称", example = "总部")
    private String orgName;
}
