package com.zeroone.star.j5.appoint.service.impl;

import cn.hutool.core.bean.BeanUtil;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j5.appoint.DO.AppointmentDO;
import com.zeroone.star.j5.appoint.VO.AppointmentCalendarVO;
import com.zeroone.star.j5.appoint.mapper.AppointmentMapper;
import com.zeroone.star.j5.appoint.service.IAppointmentService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.appoint.AppointmentCalendarDTO;
import com.zeroone.star.project.dto.j5.studentleave.StudentLeaveListDTO;
import com.zeroone.star.project.query.j5.appoint.AppointmentCalendarQuery;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

/**
 * <p>
 * 预约记录 服务实现类
 * </p>
 *
 * @author xiaoke
 * @since 2026-03-26
 */
@Service
public class AppointmentServiceImpl extends ServiceImpl<AppointmentMapper, AppointmentDO> implements IAppointmentService {

    @Autowired
    private AppointmentMapper appointmentMapper;

    /**
     * 获取预约日历（条件）
     * @param query
     * @return
     */
    @Override
    public List<AppointmentCalendarDTO> listAppointmentCalendar(AppointmentCalendarQuery query) {

        List<AppointmentCalendarVO> result = appointmentMapper.selectAppointmentInfoTimeInterval(query);

        List<AppointmentCalendarDTO> dtos = new ArrayList<>();
        for (AppointmentCalendarVO vo : result) {
            // 定义转换规则将 VO 转换为 DTO
            AppointmentCalendarDTO dto = BeanUtil.copyProperties(vo, AppointmentCalendarDTO.class);
            // 拼接课程信息字段
            LocalDateTime dateTime = LocalDateTime.of(vo.getDate(), vo.getStartTime());
            dto.setLessonTime(dateTime.toString());
            dtos.add(dto);
        }

        return dtos;
    }


}
