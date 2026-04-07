package com.zeroone.star.j5.appoint.service.impl;

import cn.hutool.core.bean.BeanUtil;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j5.appoint.entity.Appointment;
import com.zeroone.star.j5.appoint.mapper.AppointmentMapper;
import com.zeroone.star.j5.appoint.service.IAppointmentService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.appoint.AppointmentCalendarDTO;
import com.zeroone.star.project.query.j5.appoint.AppointmentCalendarQuery;
import com.zeroone.star.project.query.j5.appoint.AppointmentQuery;
import com.zeroone.star.project.vo.j5.appoint.AppointmentCalendarVO;
import com.zeroone.star.project.vo.j5.appoint.AppointmentDetailVO;
import com.zeroone.star.project.vo.j5.appoint.AppointmentListVO;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;

/**
 * <p>
 * 预约记录 服务实现类
 * </p>
 *
 * @author makise
 * @since 2026-03-23
 */
@Service
public class AppointmentServiceImpl extends ServiceImpl<AppointmentMapper, Appointment> implements IAppointmentService {
    @Resource
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


    @Override
    public PageDTO<AppointmentListVO> queryAppointmentPage(AppointmentQuery appointmentQuery) {
        Page<AppointmentListVO> pageParam = new Page<>(appointmentQuery.getPageIndex(), appointmentQuery.getPageSize());

        Page<AppointmentListVO> pageResult= baseMapper.selectAppointmentPage(pageParam,appointmentQuery);

        // （将状态枚举值转为中文）
        List<AppointmentListVO> records = pageResult.getRecords();
        if (records != null) {
            for (AppointmentListVO vo : records) {
                // 填充审核状态文本
                vo.setVerifyStateText(convertStateToText(vo.getVerifyState()));
            }
        }

        return PageDTO.create(pageResult);
    }

    @Override
    public AppointmentDetailVO getAppointmentDetailById(Long id) {
        AppointmentDetailVO vo = baseMapper.selectAppointmentDetailById(id);

        if (vo != null) {
            if (vo.getRawCourseType() != null) {
                switch (vo.getRawCourseType()) {
                    case 1: vo.setCourseType("大课"); break;
                    case 2: vo.setCourseType("小班课"); break;
                    case 3: vo.setCourseType("一对一"); break;
                    default: vo.setCourseType("未知类型");
                }
            }

            if (vo.getRawState() != null) {
                switch (vo.getRawState()) {
                    case 1: vo.setStatusText("待上课"); break;
                    case 2: vo.setStatusText("已结课"); break;
                    default: vo.setStatusText("未知状态");
                }
            }

            // 拼装时间字符串：2026-01-19(一) 11:00 ~ 12:30
            if (vo.getRawDate() != null && vo.getRawStartTime() != null && vo.getRawEndTime() != null) {
                String[] weekDays = {"日", "一", "二", "三", "四", "五", "六"};
                // 巧妙计算星期几：LocalDate.getDayOfWeek().getValue() 返回 1(一) 到 7(日)
                int dayIndex = vo.getRawDate().getDayOfWeek().getValue() % 7;

                // 使用 DateTimeFormatter 确保时间输出是严格的 HH:mm 格式
                DateTimeFormatter timeFormatter = DateTimeFormatter.ofPattern("HH:mm");
                String startTimeStr = vo.getRawStartTime().format(timeFormatter);
                String endTimeStr = vo.getRawEndTime().format(timeFormatter);

                String timeText = String.format("%s(%s) %s ~ %s",
                        vo.getRawDate().toString(),
                        weekDays[dayIndex],
                        startTimeStr,
                        endTimeStr);

                vo.setLessonTimeText(timeText);
            } else {
                vo.setLessonTimeText("时间待定");
            }
        }

        return vo;
    }

    @Override
    public boolean confirmAppointments(List<Long> ids) {
        //TODO 从token取出当前操作者的userid
        Long staffId = 3001L;
        LambdaUpdateWrapper<Appointment> updateWrapper = new LambdaUpdateWrapper<>();
        updateWrapper.in(Appointment::getId, ids)
                .eq(Appointment::getVerifyState,1);
        updateWrapper.set(Appointment::getVerifyState,2)
                .set(Appointment::getVerifyTime, LocalDateTime.now())
                .set(Appointment::getVerifyStaff,staffId);

        return this.update(updateWrapper);
    }

    @Override
    public boolean cancelAppointments(List<Long> ids) {
        //TODO 从token取出当前操作者的userid
        Long staffId = 3001L;
        LambdaUpdateWrapper<Appointment> updateWrapper = new LambdaUpdateWrapper<>();
        updateWrapper.in(Appointment::getId, ids)
                .eq(Appointment::getVerifyState,1);
        updateWrapper.set(Appointment::getVerifyState,3)
                .set(Appointment::getVerifyTime, LocalDateTime.now())
                .set(Appointment::getVerifyStaff,staffId);

        return this.update(updateWrapper);
    }

    private String convertStateToText(Integer state) {
        if (state == null) return "未知";
        switch (state) {
            case 1: return "待审核";
            case 2: return "审核通过";
            case 3: return "已驳回";
            default: return "未知";
        }
    }

}
