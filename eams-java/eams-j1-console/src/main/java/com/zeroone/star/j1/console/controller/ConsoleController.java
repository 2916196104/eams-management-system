package com.zeroone.star.j1.console.controller;

import com.zeroone.star.project.query.j1.console.*;
import com.zeroone.star.j1.console.service.IConsoleService;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.console.*;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

/**
 * <p>
 * 描述：控制台控制器
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@RestController
@Api(tags = "控制台管理")
@RequestMapping("/console")
public class ConsoleController {
    
    @Autowired
    private IConsoleService consoleService;
    
    @ApiOperation(value = "获取统计面板数据", notes = "返回教务系统关键统计数据，包括学生数、教师数、课程数等")
    @GetMapping("/statistics")
    public JsonVO<ConsoleStatisticsVO> getStatistics() {
        ConsoleStatisticsVO vo = consoleService.getStatistics();
        return JsonVO.success(vo);
    }
    
    @ApiOperation(value = "获取本月报名统计数据", notes = "返回指定月份的报名趋势和每日报名数据")
    @PostMapping("/month-enrollment")
    public JsonVO<MonthEnrollmentVO> getMonthEnrollment(@RequestBody MonthEnrollmentQuery query) {
        MonthEnrollmentVO vo = consoleService.getMonthEnrollment(query);
        return JsonVO.success(vo);
    }
    
    @ApiOperation(value = "获取课程报名统计", notes = "返回所有课程的报名情况统计，支持条件筛选")
    @PostMapping("/course-enrollment")
    public JsonVO<CourseEnrollmentVO> getCourseEnrollment(@RequestBody CourseEnrollmentQuery query) {
        CourseEnrollmentVO vo = consoleService.getCourseEnrollment(query);
        return JsonVO.success(vo);
    }
    
    @ApiOperation(value = "获取我的课表", notes = "返回指定用户的课程安排表")
    @PostMapping("/schedule")
    public JsonVO<ScheduleVO> getSchedule(@RequestBody ScheduleQuery query) {
        ScheduleVO vo = consoleService.getSchedule(query);
        return JsonVO.success(vo);
    }
    
    @ApiOperation(value = "获取我的客户列表", notes = "返回负责的客户信息及跟进状态统计")
    @PostMapping("/customer")
    public JsonVO<CustomerVO> getCustomers(@RequestBody CustomerQuery query) {
        CustomerVO vo = consoleService.getCustomers(query);
        return JsonVO.success(vo);
    }
}
