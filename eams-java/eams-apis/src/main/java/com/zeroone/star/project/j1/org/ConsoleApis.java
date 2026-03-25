package com.zeroone.star.project.j1.org;

import com.zeroone.star.project.query.j1.console.*;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.console.*;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

@Api(tags = "控制台管理")
@RequestMapping("/console")
public interface ConsoleApis {

    @ApiOperation(value = "获取统计面板数据", notes = "返回教务系统关键统计数据，包括学生数、教师数、课程数等")
    @GetMapping("/statistics")
    JsonVO<ConsoleStatisticsVO> getStatistics();

    @ApiOperation(value = "获取本月报名统计数据", notes = "返回指定月份的报名趋势和每日报名数据")
    @PostMapping("/month-enrollment")
    JsonVO<MonthEnrollmentVO> getMonthEnrollment(@RequestBody MonthEnrollmentQuery query);

    @ApiOperation(value = "获取课程报名统计", notes = "返回所有课程的报名情况统计，支持条件筛选")
    @PostMapping("/course-enrollment")
    JsonVO<CourseEnrollmentVO> getCourseEnrollment(@RequestBody CourseEnrollmentQuery query);

    @ApiOperation(value = "获取我的课表", notes = "返回指定用户的课程安排表")
    @PostMapping("/schedule")
    JsonVO<ScheduleVO> getSchedule(@RequestBody ScheduleQuery query);

    @ApiOperation(value = "获取我的客户列表", notes = "返回负责的客户信息及跟进状态统计")
    @PostMapping("/customer")
    JsonVO<CustomerVO> getCustomers(@RequestBody CustomerQuery query);
}
