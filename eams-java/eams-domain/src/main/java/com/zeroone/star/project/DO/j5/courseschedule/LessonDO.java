package com.zeroone.star.project.DO.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;

@Data
@ApiModel(description = "课次DO")
public class LessonDO {
    @ApiModelProperty(value = "ID")
    private Long id;
    @ApiModelProperty(value = "标题")
    private String title;
    @ApiModelProperty(value = "序号")
    private Integer sn;
    @ApiModelProperty(value = "课程ID")
    private Long courseId;
    @ApiModelProperty(value = "排课ID")
    private Long scheduleId;
    @ApiModelProperty(value = "班级ID")
    private Long classId;
    @ApiModelProperty(value = "教室ID")
    private Long roomId;
    @ApiModelProperty(value = "上课日期")
    private LocalDate date;
    @ApiModelProperty(value = "开始时间")
    private LocalTime startTime;
    @ApiModelProperty(value = "结束时间")
    private LocalTime endTime;
    @ApiModelProperty(value = "创建人")
    private Long creator;
    @ApiModelProperty(value = "编辑人")
    private Long editor;
    @ApiModelProperty(value = "创建时间")
    private LocalDateTime addTime;
    @ApiModelProperty(value = "编辑时间")
    private LocalDateTime editTime;
    @ApiModelProperty(value = "删除标记")
    private Integer deleted;
    @ApiModelProperty(value = "应扣次数")
    private Integer decCount;
    @ApiModelProperty(value = "备注")
    private String remark;
    @ApiModelProperty(value = "授课类型")
    private Integer teachType;
    @ApiModelProperty(value = "是否试听")
    private Integer onTrial;
    @ApiModelProperty(value = "试听结果")
    private String trialResult;
    @ApiModelProperty(value = "状态")
    private Integer state;
    @ApiModelProperty(value = "结课时间")
    private LocalDateTime closeTime;
    @ApiModelProperty(value = "结课人")
    private Long closeOperator;
    @ApiModelProperty(value = "教师ID")
    private Long teacherId;
    @ApiModelProperty(value = "是否可预约")
    private Integer bookable;
    @ApiModelProperty(value = "学校ID")
    private Long schoolId;
    @ApiModelProperty(value = "机构ID")
    private Long orgId;
}