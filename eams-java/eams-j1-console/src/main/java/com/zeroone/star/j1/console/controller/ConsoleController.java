package com.zeroone.star.j1.console.controller;

import com.zeroone.star.j1.console.service.IConsoleService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j1.ConsoleApis;
import com.zeroone.star.project.query.j1.console.*;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.console.*;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;

/**
 * <p>
 * 控制台管理控制器
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@RestController
@Api(tags = "控制台管理")
public class ConsoleController implements ConsoleApis {

    @Resource
    private IConsoleService consoleService;

    @Override
    @GetMapping("/console/statistics")
    @ApiOperation(value = "统计面板", notes = "获取控制台统计面板数据")
    public JsonVO<ConsoleStatisticsVO> getStatistics() {
        return JsonVO.success(consoleService.getStatistics());
    }

    @Override
    @GetMapping("/console/month-enrollment")
    @ApiOperation(value = "本月报名", notes = "获取本月报名走势数据")
    public JsonVO<MonthEnrollmentVO> getMonthEnrollment(MonthEnrollmentQuery query) {
        return JsonVO.success(consoleService.getMonthEnrollment(query));
    }

    @Override
    @GetMapping("/console/course-enrollment-rank")
    @ApiOperation(value = "课程报名排行", notes = "获取课程报名金额前5排行")
    public JsonVO<List<CourseEnrollmentRankVO>> getCourseEnrollmentRank() {
        return JsonVO.success(consoleService.getCourseEnrollmentRank());
    }

    @Override
    @PostMapping("/console/schedule")
    @ApiOperation(value = "课表日历", notes = "查询控制台课表日历数据")
    public JsonVO<TimetableCalendarVO> getSchedule(@RequestBody TimetableCalendarQuery query) {
        return JsonVO.success(consoleService.getTimetableCalendar(query));
    }

    @Override
    @PostMapping("/console/my-customer")
    @ApiOperation(value = "我的客户", notes = "分页查询我的客户列表")
    public JsonVO<MyCustomerVO> getMyCustomerList(@RequestBody MyCustomerQuery query) {
        return JsonVO.success(consoleService.getMyCustomerList(query));
    }

    @Override
    @PostMapping("/console/my-enrollment")
    @ApiOperation(value = "获取我的报名列表", notes = "返回当前用户的报名记录，支持分页")
    public JsonVO<PageDTO<MyEnrollmentVO>> getMyEnrollment(@RequestBody MyEnrollmentQuery query) {
        return JsonVO.success(consoleService.getMyEnrollment(query));
    }

    @Override
    @PostMapping("/console/announcement")
    @ApiOperation(value = "获取控制台公告列表", notes = "返回公告列表，支持分页")
    public JsonVO<PageDTO<AnnouncementVO>> getAnnouncement(@RequestBody AnnouncementQuery query) {
        return JsonVO.success(consoleService.getAnnouncement(query));
    }

    @Override
    @PostMapping("/console/my-follow")
    @ApiOperation(value = "获取我的跟进列表", notes = "返回跟进记录，支持分页")
    public JsonVO<PageDTO<MyFollowVO>> getMyFollow(@RequestBody MyFollowQuery query) {
        return JsonVO.success(consoleService.getMyFollow(query));
    }

    @Override
    @PostMapping("/console/my-payment")
    @ApiOperation(value = "获取我的请款列表", notes = "返回请款记录，支持分页")
    public JsonVO<PageDTO<MyPaymentVO>> getMyPayment(@RequestBody MyPaymentQuery query) {
        return JsonVO.success(consoleService.getMyPayment(query));
    }

    @Override
    @PostMapping("/console/schedule-calendar")
    @ApiOperation(value = "获取课表日历数据", notes = "返回课表列表，支持分页")
    public JsonVO<PageDTO<ScheduleCalendarVO>> getScheduleCalendar(@RequestBody ScheduleCalendarQuery query) {
        return JsonVO.success(consoleService.getScheduleCalendar(query));
    }
}
