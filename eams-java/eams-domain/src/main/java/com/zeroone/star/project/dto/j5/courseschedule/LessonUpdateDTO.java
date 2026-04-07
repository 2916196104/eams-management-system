package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;
import java.time.LocalTime;

@Data
@ApiModel(value = "课次新增DTO", description = "课次新增参数")
public class LessonUpdateDTO {
    @ApiModelProperty(value = "标题")
    private String title;

    @ApiModelProperty(value = "序号")
    private Integer sn;

    @ApiModelProperty(value = "课程ID")
    private Long courseId;

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

    @ApiModelProperty(value = "应扣次数")
    private Integer decCount;

    @ApiModelProperty(value = "备注")
    private String remark;

    @ApiModelProperty(value = "授课类型")
    private Integer teachType;

    @ApiModelProperty(value = "是否试听")
    private Integer onTrial;

    @ApiModelProperty(value = "教师ID")
    private Long teacherId;
}
