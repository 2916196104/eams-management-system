package com.zeroone.star.project.vo.j5.appoint;

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

    @ApiModelProperty(value = "学生姓名和电话", example = "小明 13254856729")
    private String studentNameAndPhone;


    @ApiModelProperty(value = "预约课程", example = "C语言")
    private String lessonTitle;

    @ApiModelProperty(value = "上课日期", example = "2026-03-15")
    @JsonFormat(pattern = "yyyy-MM-dd")
    private LocalDate date;

    @ApiModelProperty(value = "审核状态", example = "已审核")
    private String verifyState;


}
