package com.zeroone.star.project.j1;

import com.zeroone.star.project.query.j1.console.*;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.console.*;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * <p>
 * 描述：控制台 API 接口定义
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@Api(tags = "控制台管理")
public interface ConsoleApis {

    /**
     * 统计面板
     *
     * @return 统计面板数据
     */
    @ApiOperation(value = "统计面板", notes = "获取控制台统计面板数据")
    @GetMapping("/console/statistics")
    JsonVO<ConsoleStatisticsVO> getStatistics();

    /**
     * 本月报名走势
     *
     * @param query 查询参数（年份、月份）
     * @return 本月报名走势数据
     */
    @ApiOperation(value = "本月报名", notes = "获取本月报名走势数据")
    @GetMapping("/console/month-enrollment")
    JsonVO<MonthEnrollmentVO> getMonthEnrollment(MonthEnrollmentQuery query);

    /**
     * 课程报名金额排行（前5）
     *
     * @return 课程报名金额排行列表
     */
    @ApiOperation(value = "课程报名排行", notes = "获取课程报名金额前5排行")
    @GetMapping("/console/course-enrollment-rank")
    JsonVO<List<CourseEnrollmentRankVO>> getCourseEnrollmentRank();

    /**
     * 课表日历
     *
     * @param query 查询参数（周期、班级、课程、科目、老师、学生）
     * @return 课表日历数据
     */
    @ApiOperation(value = "课表日历", notes = "查询指定周期的课表日历数据")
    @PostMapping("/console/schedule")
    JsonVO<TimetableCalendarVO> getSchedule(@RequestBody TimetableCalendarQuery query);

    /**
     * 我的客户（分页查询）
     *
     * @param query 查询参数（学员姓名、联系电话、学习阶段、性别、日期范围、分页）
     * @return 客户列表
     */
    @ApiOperation(value = "我的客户", notes = "分页查询我的客户列表")
    @PostMapping("/console/my-customer")
    JsonVO<MyCustomerVO> getMyCustomerList(@RequestBody MyCustomerQuery query);
}
