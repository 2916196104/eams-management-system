package com.zeroone.star.j1.console.controller;

import com.zeroone.star.project.j1.ConsoleApis;
import com.zeroone.star.project.query.j1.console.ConsoleNoticeQuery;
import com.zeroone.star.project.query.j1.console.MyFollowUpQuery;
import com.zeroone.star.project.query.j1.console.MyPaymentRequestQuery;
import com.zeroone.star.project.query.j1.console.MyRegistrationQuery;
import com.zeroone.star.project.query.j1.console.TimetableCalendarQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.console.ConsoleNoticeVO;
import com.zeroone.star.project.vo.j1.console.MyFollowUpVO;
import com.zeroone.star.project.vo.j1.console.MyPaymentRequestVO;
import com.zeroone.star.project.vo.j1.console.MyRegistrationVO;
import com.zeroone.star.project.vo.j1.console.TimetableCalendarVO;
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
    public JsonVO<MyRegistrationVO> getCourseEnrollment(@RequestBody MyRegistrationQuery query) {
        return JsonVO.success(new MyRegistrationVO());
    }

    @Override
    @ApiOperation(value = "公告数据", notes = "分页查询控制台公告数据")
    @PostMapping("/console/notice")
    public JsonVO<ConsoleNoticeVO> getNoticeList(@RequestBody ConsoleNoticeQuery query) {
        return JsonVO.success(new ConsoleNoticeVO());
    }

    @Override
    @ApiOperation(value = "我的跟进", notes = "分页查询我的跟进记录")
    @PostMapping("/console/customer")
    public JsonVO<MyFollowUpVO> getCustomers(@RequestBody MyFollowUpQuery query) {
        return JsonVO.success(new MyFollowUpVO());
    }

    @Override
    @ApiOperation(value = "我的请款", notes = "分页查询我的请款记录")
    @PostMapping("/console/cashout")
    public JsonVO<MyPaymentRequestVO> getCashoutList(@RequestBody MyPaymentRequestQuery query) {
        return JsonVO.success(new MyPaymentRequestVO());
    }

    @Override
    @ApiOperation(value = "课表日历", notes = "查询控制台课表日历数据")
    @PostMapping("/console/schedule")
    public JsonVO<TimetableCalendarVO> getSchedule(@RequestBody TimetableCalendarQuery query) {
        return JsonVO.success(new TimetableCalendarVO());
    }
}
