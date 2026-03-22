package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalTime;
import java.util.List;

@Data
@ApiModel("批量修改课次 DTO")
public class BatchUpdateCourseDTO {

    @ApiModelProperty(value = "需要修改的课表ID集合", required = true)
    private List<Long> lessonIds;

    @ApiModelProperty(value = "调整天数（-7到7）", example = "1")
    private Integer dayOffset;


    @ApiModelProperty(value = "新上课老师ID")
    private Long teacherId;

    @ApiModelProperty(value = "新上课老师名称")
    private String teacherName;

    @ApiModelProperty(value = "新助教ID")
    private Long assistantId;

    @ApiModelProperty(value = "新助教名称")
    private String assistantName;

    @ApiModelProperty(value = "新教室ID")
    private Long classroomId;

    @ApiModelProperty(value = "新教室名称")
    private String classroomName;

    @ApiModelProperty(value = "新开始时间")
    @DateTimeFormat(pattern = "HH:mm")
    private LocalTime startTime;

    @ApiModelProperty(value = "新结束时间")
    @DateTimeFormat(pattern = "HH:mm")
    private LocalTime endTime;
}
