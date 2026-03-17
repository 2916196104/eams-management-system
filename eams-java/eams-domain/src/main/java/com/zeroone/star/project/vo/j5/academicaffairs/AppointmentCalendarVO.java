package com.zeroone.star.project.vo.j5.academicaffairs;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;

/**
 * <p>
 * 描述：预约日历 VO
 * </p>
 *
 * @author : 小可
 * @date : 2026/3/15 16:58
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
@ApiModel("预约日历 VO")
public class AppointmentCalendarVO {

    @ApiModelProperty(value = "预约表 id", example = "2008418408000000001")
    private Long id;

    @ApiModelProperty(value = "学生姓名", example = "小明")
    private String studentName;

    @ApiModelProperty(value = "学生电话", example = "13254856729")
    private String mobile;

    @ApiModelProperty(value = "预约课程", example = "C语言")
    private String lessonTitle;

    @ApiModelProperty(value = "上课日期", example = "2026-03-15")
    @JsonFormat(pattern = "yyyy-MM-dd")
    private LocalDate date;

    @ApiModelProperty(value = "开始时间", example = "10:00")
    @JsonFormat(pattern = "hh:mm")
    private LocalTime startTime;

    @ApiModelProperty(value = "结束时间", example = "10:00")
    @JsonFormat(pattern = "hh:mm")
    private LocalTime endTime;

    @ApiModelProperty(value = "预约时间", example = "2026-03-12 10:00:00")
    @JsonFormat(pattern = "yyyy-MM-dd hh:mm:ss")
    private LocalDateTime addTime;

    @ApiModelProperty(value = "备注", example = "无")
    private String remark;

    @ApiModelProperty(value = "审核状态", example = "已审核")
    private String verifyState;

    @ApiModelProperty(value = "审核时间", example = "2026-03-14 10:00:00")
    @JsonFormat(pattern = "yyyy-MM-dd hh:mm:ss")
    private LocalDateTime verifyTime;

    @ApiModelProperty(value = "审核人", example = "管理员")
    private String verifyStaff;

    @ApiModelProperty(value = "审核内容", example = "审核通过....")
    private String verifyRemark;

}
