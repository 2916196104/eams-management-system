package com.zeroone.star.project.j5.appoint;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.appoint.AppointmentCalendarDTO;
import com.zeroone.star.project.query.j5.appoint.AppointmentCalendarQuery;
import com.zeroone.star.project.query.j5.appoint.AppointmentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.appoint.AppointmentDetailVO;
import com.zeroone.star.project.vo.j5.appoint.AppointmentListVO;

import java.util.List;

/**
 * <p>
 * 预约接口声明
 * </p>
 *
 * @author makise
 * @since 2026/3/23
 */
public interface AppointmentApis {
    /**
     * @return
     */
    /**
     * 获取预约日历（条件）
     * @param appointmentCalendarQuery
     * @return
     */
    JsonVO<List<AppointmentCalendarDTO>> queryAppointmentCalendar(AppointmentCalendarQuery appointmentCalendarQuery);

    /**
     * 分页查询预约列表
     * @param appointmentQuery
     * @return
     */
    JsonVO<PageDTO<AppointmentListVO>> queryPage(AppointmentQuery appointmentQuery);


    /**
     * 获取课程详情
     * @param id
     * @return
     */
    JsonVO<AppointmentDetailVO> getAppointmentDetail(Long id);


    /**
     * 确认预约 (支持批量操作)
     * @param ids 预约记录ID集合
     * @return
     */
    JsonVO<List<Long>> confirmAppointment(List<Long> ids);

    /**
     * 取消预约 (支持批量操作)
     * @param ids 预约记录ID集合
     * @return
     */
    JsonVO<List<Long>> cancelAppointment(List<Long> ids);

}
