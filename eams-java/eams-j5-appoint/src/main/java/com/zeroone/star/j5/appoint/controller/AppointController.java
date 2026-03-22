package com.zeroone.star.j5.appoint.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.appoint.AppointmentDTO;
import com.zeroone.star.project.j5.appoint.AppointmentApis;
import com.zeroone.star.project.query.j5.appoint.AppointmentCalendarQuery;
import com.zeroone.star.project.query.j5.appoint.AppointmentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.appoint.AppointmentCalendarVO;
import com.zeroone.star.project.vo.j5.appoint.AppointmentDetailVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * <p>
 * 描述：预约管理相关 Controller
 * </p>
 *
 * @author : 小可
 * @date : 2026/3/16 20:55
 */
@RestController
@RequestMapping("/appoint")
@Slf4j
@Api(tags = "预约管理")
public class AppointController implements AppointmentApis {

    @Override
    @ApiOperation("获取预约日历（条件）")
    @GetMapping("/j5/calendar")
    public JsonVO<List<AppointmentCalendarVO>> queryAppointmentCalendar(AppointmentCalendarQuery appointmentCalendarQuery) {
        return null;
    }

    @GetMapping
    @ApiOperation("获取预约列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<AppointmentDTO>> queryPage(AppointmentQuery appointmentQuery) {
        return null;
    }


    @GetMapping("/{id}")
    @ApiOperation("获取预约课程详情")
    @Override
    public JsonVO<AppointmentDetailVO> getAppointmentDetail(@PathVariable("id") Long id) {
        return null;
    }

    @PostMapping("/confirm")
    @ApiOperation("确认预约（支持批量操作）")
    @Override
    public JsonVO<List<Long>> confirmAppointment(@RequestBody List<Long> ids) {
        return null;
    }

    @PostMapping("/cancel")
    @ApiOperation("取消预约（支持批量操作）")
    @Override
    public JsonVO<List<Long>> cancelAppointment(@RequestBody List<Long> ids) {
        return null;
    }

}
