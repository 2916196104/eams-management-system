package com.zeroone.star.j5.appoint.controller;

import com.zeroone.star.project.j5.appoint.AppointmentApis;
import com.zeroone.star.project.query.j5.appoint.AppointmentCalendarQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.appoint.AppointmentCalendarVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

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

}
