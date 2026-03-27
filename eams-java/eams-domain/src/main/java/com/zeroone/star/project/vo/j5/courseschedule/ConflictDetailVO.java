package com.zeroone.star.project.vo.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.io.Serializable;

/**
 * 冲突详情VO
 *
 * @author j5-courseschedule
 * @since 2026-03-17
 */
@Data
@ApiModel(description = "冲突详情VO")
public class ConflictDetailVO implements Serializable {

    private static final long serialVersionUID = 1L;

    @ApiModelProperty(value = "排课计划ID", example = "1001")
    private Long scheduleId;

    @ApiModelProperty(value = "冲突类型代码", example = "TEACHER_TIME",
            allowableValues = "TEACHER_TIME,ROOM_OCCUPIED,CLASS_TIME")
    private String conflictType;

    @ApiModelProperty(value = "冲突类型名称", example = "教师时间冲突")
    private String conflictTypeName;

    @ApiModelProperty(value = "冲突的排课计划ID或课次ID", example = "1005")
    private Long conflictWith;

    @ApiModelProperty(value = "冲突的时间段描述", example = "2026-03-20 09:00-10:00")
    private String conflictTime;

    @ApiModelProperty(value = "冲突对象名称", example = "张老师")
    private String conflictObjectName;

    @ApiModelProperty(value = "冲突日期", example = "2026-03-20")
    private String conflictDate;

    @ApiModelProperty(value = "冲突开始时间", example = "09:00:00")
    private String conflictStartTime;

    @ApiModelProperty(value = "冲突结束时间", example = "10:00:00")
    private String conflictEndTime;

    @ApiModelProperty(value = "冲突教室名称", example = "A101教室")
    private String roomName;

    @ApiModelProperty(value = "冲突班级名称", example = "Python基础班01期")
    private String className;
}
