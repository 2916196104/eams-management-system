package com.zeroone.star.project.j1;

import com.zeroone.star.project.query.j1.console.*;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.console.*;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

/**
 * <p>
 * 描述：控制台 API 接口定义
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author xiaoyang
 * @version 1.0.0
 */
@Api(tags = "控制台管理")
public interface ConsoleApis {

    /**
     * 我的报名（分页查询）
     *
     * @param query 查询参数（学员姓名/电话、开始日期范围、分页）
     * @return 报名列表
     */
    @ApiOperation(value = "我的报名", notes = "分页查询报名签约列表")
    @PostMapping("/console/course-enrollment")
    JsonVO<MyRegistrationVO> getCourseEnrollment(@RequestBody MyRegistrationQuery query);

    /**
     * 控制台-公告数据（分页查询）
     *
     * @param query 查询参数（标题、分页）
     * @return 公告列表
     */
    @ApiOperation(value = "公告数据", notes = "分页查询控制台公告列表")
    @PostMapping("/console/notice")
    JsonVO<ConsoleNoticeVO> getNoticeList(@RequestBody ConsoleNoticeQuery query);

    /**
     * 我的跟进（分页查询）
     *
     * @param query 查询参数（学员姓名/电话、跟进阶段、日期范围、分页）
     * @return 跟进列表
     */
    @ApiOperation(value = "我的跟进", notes = "分页查询跟进记录列表")
    @PostMapping("/console/customer")
    JsonVO<MyFollowUpVO> getCustomers(@RequestBody MyFollowUpQuery query);

    /**
     * 我的请款（分页查询）
     *
     * @param query 查询参数（日期范围、审核状态、分页）
     * @return 请款列表
     */
    @ApiOperation(value = "我的请款", notes = "分页查询请款记录列表")
    @PostMapping("/console/cashout")
    JsonVO<MyPaymentRequestVO> getCashoutList(@RequestBody MyPaymentRequestQuery query);

    /**
     * 控制台-课表日历
     *
     * @param query 查询参数（周期、班级、课程、老师、学生）
     * @return 课表日历数据
     */
    @ApiOperation(value = "课表日历", notes = "查询指定周期的课表日历数据")
    @PostMapping("/console/schedule")
    JsonVO<TimetableCalendarVO> getSchedule(@RequestBody TimetableCalendarQuery query);
}
