package com.zeroone.star.j5.appoint.mapper;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j5.appoint.entity.Appointment;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.query.j5.appoint.AppointmentCalendarQuery;
import com.zeroone.star.project.query.j5.appoint.AppointmentQuery;
import com.zeroone.star.project.vo.j5.appoint.AppointmentCalendarVO;
import com.zeroone.star.project.vo.j5.appoint.AppointmentDetailVO;
import com.zeroone.star.project.vo.j5.appoint.AppointmentListVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * <p>
 * 预约记录 Mapper 接口
 * </p>
 *
 * @author makise
 * @since 2026-03-23
 */
@Mapper
public interface AppointmentMapper extends BaseMapper<Appointment> {

    List<AppointmentCalendarVO> selectAppointmentInfoTimeInterval(AppointmentCalendarQuery query);

    /**
     * 多表联查分页sql
     * @param pageParam
     * @param appointmentQuery
     * @return
     */
    Page<AppointmentListVO> selectAppointmentPage(Page<AppointmentListVO> pageParam,
                                                  @Param("query")AppointmentQuery appointmentQuery);

    /**
     * 获取预约课程详情
     * @param id
     * @return
     */
    AppointmentDetailVO selectAppointmentDetailById(@Param("id")Long id);
}
