package com.zeroone.star.j5.appoint.mapper;

import com.zeroone.star.project.DO.j5.appoint.AppointmentDO;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.vo.j5.appoint.AppointmentCalendarVO;
import com.zeroone.star.project.query.j5.appoint.AppointmentCalendarQuery;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

/**
 * <p>
 * 预约记录 Mapper 接口
 * </p>
 *
 * @author xiaoke
 * @since 2026-03-26
 */
@Mapper
public interface AppointmentMapper extends BaseMapper<AppointmentDO> {

    List<AppointmentCalendarVO> selectAppointmentInfoTimeInterval(AppointmentCalendarQuery query);
}
