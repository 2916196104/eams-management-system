package com.zeroone.star.j5.appoint.service;

import com.zeroone.star.project.DO.j5.appoint.AppointmentDO;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.j5.appoint.AppointmentCalendarDTO;
import com.zeroone.star.project.query.j5.appoint.AppointmentCalendarQuery;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * <p>
 * 预约记录 服务类
 * </p>
 *
 * @author xiaoke
 * @since 2026-03-26
 */
@Service
public interface IAppointmentService extends IService<AppointmentDO> {

    /**
     * 获取预约日历（条件）
     * @param appointmentCalendarQuery
     * @return
     */
    List<AppointmentCalendarDTO> listAppointmentCalendar(AppointmentCalendarQuery appointmentCalendarQuery);
}
