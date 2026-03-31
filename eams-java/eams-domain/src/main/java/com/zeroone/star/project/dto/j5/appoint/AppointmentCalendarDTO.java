package com.zeroone.star.project.dto.j5.appoint;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDate;

/**
 * <p>
 * 描述：预约日历 DTO
 * </p>
 *
 * @author : 小可
 * @date : 2026/3/15 16:58
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
@ApiModel("预约日历 DTO")
public class AppointmentCalendarDTO {

    @ApiModelProperty(value = "预约表 id", example = "2008418408000000001")
    private Long id;

    @ApiModelProperty(value = "学生姓名", example = "小明")
    private String studentName;

    @ApiModelProperty(value = "手机号码", example = "13254856729")
    private String mobile;

    @ApiModelProperty(value = "预约课程", example = "C语言")
    private String lessonTitle;

    @ApiModelProperty(value = "上课时间", example = "2026-03-15 10:00:00")
    private String lessonTime;

    @ApiModelProperty(value = "预约时间", example = "2026-03-14 10:00")
    private String appointTime;

    @ApiModelProperty(value = "审核人", example = "管理员")
    private String verifyStaff;

    @ApiModelProperty(value = "审核状态", example = "已审核")
    private String verifyState;

    @ApiModelProperty(value = "备注", example = "无")
    private String remark;

}
