package com.zeroone.star.project.j5.appoint;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.appoint.AppointmentDTO;
import com.zeroone.star.project.query.j5.appoint.AppointmentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.appoint.AppointmentDetailVO;

import java.util.List;

/**
 * 预约接口声明
 */
public interface AppointmentApis {
    /**
     * 分页查询预约列表
     * @param appointmentQuery
     * @return
     */
    JsonVO<PageDTO<AppointmentDTO>> queryPage(AppointmentQuery appointmentQuery);


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
