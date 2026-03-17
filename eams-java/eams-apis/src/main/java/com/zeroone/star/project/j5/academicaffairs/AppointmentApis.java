package com.zeroone.star.project.j5.academicaffairs;

import com.zeroone.star.project.query.j5.academicaffairs.AppointmentCalendarQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.academicaffairs.AppointmentCalendarVO;

import java.util.List;

/**
 * <p>
 * 描述：预约相关接口定义
 * </p>
 *
 * @author : 小可
 * @date : 2026/3/15 18:21
 */
public interface AppointmentApis {

    /**
     * 获取预约日历（条件）
     * @param appointmentCalendarQuery
     * @return
     */
    JsonVO<List<AppointmentCalendarVO>> queryAppointmentCalendar(AppointmentCalendarQuery appointmentCalendarQuery);

}
