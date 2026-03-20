package com.zeroone.star.j1.console.controller;

import com.zeroone.star.project.j1.ConsoleApis;
import com.zeroone.star.project.query.j1.console.CashoutQuery;
import com.zeroone.star.project.query.j1.console.CourseEnrollmentQuery;
import com.zeroone.star.project.query.j1.console.CustomerQuery;
import com.zeroone.star.project.query.j1.console.NoticeQuery;
import com.zeroone.star.project.query.j1.console.ScheduleQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.console.CashoutVO;
import com.zeroone.star.project.vo.j1.console.CourseEnrollmentVO;
import com.zeroone.star.project.vo.j1.console.CustomerVO;
import com.zeroone.star.project.vo.j1.console.NoticeConsoleVO;
import com.zeroone.star.project.vo.j1.console.ScheduleVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
@Api(tags = "控制台管理")
public class ConsoleController implements ConsoleApis {

    @Override
    @ApiOperation(value = "我的报名", notes = "分页查询我的报名列表")
    @PostMapping("/console/course-enrollment")
    public JsonVO<CourseEnrollmentVO> getCourseEnrollment(@RequestBody CourseEnrollmentQuery query) {
        return JsonVO.success(new CourseEnrollmentVO());
    }

    @Override
    @ApiOperation(value = "公告数据", notes = "分页查询控制台公告数据")
    @PostMapping("/console/notice")
    public JsonVO<NoticeConsoleVO> getNoticeList(@RequestBody NoticeQuery query) {
        return JsonVO.success(new NoticeConsoleVO());
    }

    @Override
    @ApiOperation(value = "我的跟进", notes = "分页查询我的跟进记录")
    @PostMapping("/console/customer")
    public JsonVO<CustomerVO> getCustomers(@RequestBody CustomerQuery query) {
        return JsonVO.success(new CustomerVO());
    }

    @Override
    @ApiOperation(value = "我的请款", notes = "分页查询我的请款记录")
    @PostMapping("/console/cashout")
    public JsonVO<CashoutVO> getCashoutList(@RequestBody CashoutQuery query) {
        return JsonVO.success(new CashoutVO());
    }

    @Override
    @ApiOperation(value = "课表日历", notes = "查询控制台课表日历数据")
    @PostMapping("/console/schedule")
    public JsonVO<ScheduleVO> getSchedule(@RequestBody ScheduleQuery query) {
        return JsonVO.success(new ScheduleVO());
    }
}
