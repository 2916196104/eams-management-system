package com.zeroone.star.project.vo.j5.appoint;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDate;
import java.time.LocalTime;

/**
 * <p>
 * 描述：获取预约日历中间类
 * </p>
 *
 * @author : 小可
 * @date : 2026/3/26 13:27
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
public
class AppointmentCalendarVO {

    private Long id;

    /**
     * 学生姓名
     */
    private String studentName;

    /**
     * 手机号码
     */
    private String mobile;

    /**
     * 预约课程
     */
    private String lessonTitle;

    /**
     * 上课时间
     */
    private LocalDate date;

    /**
     * 上课开始时间
     */
    private LocalTime startTime;

    /**
     * 预约时间
     */
    private String appointTime;

    /**
     * 审核人
     */
    private String verifyStaff;

    /**
     * 审核状态
     */
    private String verifyState;

    /**
     * 备注
     */
    private String remark;

}
