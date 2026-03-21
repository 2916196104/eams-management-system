package com.zeroone.star.j1.console.controller;

import com.zeroone.star.project.j1.org.ConsoleApis;
import com.zeroone.star.project.query.j1.console.*;
import com.zeroone.star.j1.console.service.IConsoleService;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.console.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class ConsoleController implements ConsoleApis {

    @Autowired
    private IConsoleService consoleService;

    @Override
    public JsonVO<ConsoleStatisticsVO> getStatistics() {
        ConsoleStatisticsVO vo = consoleService.getStatistics();
        return JsonVO.success(vo);
    }

    @Override
    public JsonVO<MonthEnrollmentVO> getMonthEnrollment(MonthEnrollmentQuery query) {
        MonthEnrollmentVO vo = consoleService.getMonthEnrollment(query);
        return JsonVO.success(vo);
    }

    @Override
    public JsonVO<CourseEnrollmentVO> getCourseEnrollment(CourseEnrollmentQuery query) {
        CourseEnrollmentVO vo = consoleService.getCourseEnrollment(query);
        return JsonVO.success(vo);
    }

    @Override
    public JsonVO<ScheduleVO> getSchedule(ScheduleQuery query) {
        ScheduleVO vo = consoleService.getSchedule(query);
        return JsonVO.success(vo);
    }

    @Override
    public JsonVO<CustomerVO> getCustomers(CustomerQuery query) {
        CustomerVO vo = consoleService.getCustomers(query);
        return JsonVO.success(vo);
    }
}
