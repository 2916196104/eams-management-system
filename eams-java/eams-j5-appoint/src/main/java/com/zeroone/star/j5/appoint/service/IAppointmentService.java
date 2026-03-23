package com.zeroone.star.j5.appoint.service;

import com.zeroone.star.j5.appoint.entity.Appointment;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j5.appoint.AppointmentQuery;
import com.zeroone.star.project.vo.j5.appoint.AppointmentDetailVO;
import com.zeroone.star.project.vo.j5.appoint.AppointmentListVO;

import java.util.List;

/**
 * <p>
 * 预约记录 服务类
 * </p>
 *
 * @author makise
 * @since 2026-03-23
 */
public interface IAppointmentService extends IService<Appointment> {

    PageDTO<AppointmentListVO> queryAppointmentPage(AppointmentQuery appointmentQuery);

    AppointmentDetailVO getAppointmentDetailById(Long id);

    boolean confirmAppointments(List<Long> ids);

    boolean cancelAppointments(List<Long> ids);
}
