package com.zeroone.star.project.dto.j5.courseschedule;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import javax.validation.constraints.AssertTrue;
import javax.validation.constraints.NotNull;
import java.time.LocalDate;
import java.time.LocalTime;
import java.util.List;

@Data
public class UpdateCourseDTO {
    @ApiModelProperty(value = "课程ID", required = true)
    @NotNull(message = "课次ID不能为空")
    private Long id;

    @ApiModelProperty(value = "课程标题",example = "体育")
    private String title;

    @ApiModelProperty(value = "分校id",example = "1")
    private Long schoolId;

    @ApiModelProperty(value = "课程id",example = "1")
    private Long courseId;

    @ApiModelProperty(value = "主讲老师id集合(type_num=1)")
    private List<Long> teacherIds;

    @ApiModelProperty(value = "助教老师id集合(type_num=2)")
    private List<Long> assistantIds;

    @ApiModelProperty(value = "上课日期", example = "2026-01-01",required = false)
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate date;

    @ApiModelProperty(value = "开始时间", example = "05:30:00",required = false)
    @DateTimeFormat(pattern = "HH:mm")
    private LocalTime startTime;

    @ApiModelProperty(value = "结束时间", example = "05:50:00",required = false)
    @DateTimeFormat(pattern = "HH:mm")
    private LocalTime endTime;

    @ApiModelProperty(value = "教室id",example = "1")
    private Long roomId;

    @ApiModelProperty(value = "消课基数",example = "1")
    private Integer decCount;

    @ApiModelProperty(value = "是否可预约",example = "true")
    private Integer bookable;

    @ApiModelProperty(value = "是否检查冲突",example = "true")
    private Boolean checkConflict;

    /** 时间校验 */
    @AssertTrue(message = "开始时间必须早于结束时间")
    public boolean validTime() {
        if (startTime == null || endTime == null) return true;
        return startTime.isBefore(endTime);
    }

   /* @ApiModelProperty(value = "是否同步后续相同时间课次",example = "true")
    private Boolean batchUpdate;*/

}
