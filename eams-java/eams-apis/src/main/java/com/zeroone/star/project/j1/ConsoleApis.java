package com.zeroone.star.project.j1;

import com.zeroone.star.project.dto.j1.Console.StatisticsPanelDTO;
import com.zeroone.star.project.dto.j1.customer.MyCustomerDTO;
import com.zeroone.star.project.dto.j1.schedule.MyScheduleDTO;
import com.zeroone.star.project.query.j1.console.CourseEnrollmentQuery;
import com.zeroone.star.project.query.j1.console.CustomerQuery;
import com.zeroone.star.project.query.j1.console.MonthEnrollmentQuery;
import com.zeroone.star.project.query.j1.console.ScheduleQuery;
import com.zeroone.star.project.query.j1.customer.MyCustomerQuery;
import com.zeroone.star.project.query.j1.schedule.MyScheduleQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.console.ConsoleStatisticsVO;
import com.zeroone.star.project.vo.j1.console.CourseEnrollmentVO;
import com.zeroone.star.project.vo.j1.console.CustomerVO;
import com.zeroone.star.project.vo.j1.console.MonthEnrollmentVO;
import com.zeroone.star.project.vo.j1.console.ScheduleVO;
import com.zeroone.star.project.vo.j1.console.StatisticsPanelVO;
import com.zeroone.star.project.vo.j1.customer.MyCustomerVO;
import com.zeroone.star.project.vo.j1.enrollment.MonthlyEnrollmentVO;
import com.zeroone.star.project.vo.j1.schedule.MyScheduleVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;

import java.util.List;

/**
 * <p>
 * 描述：控制台相关 API 接口
 * </p>
 *
 * @author hxb
 * @version 1.0.0
 */
@Api(tags = "控制台管理")
public interface ConsoleApis {
    JsonVO<StatisticsPanelVO> getStatisticsPanel();

    JsonVO<List<MonthlyEnrollmentVO>> getMonthlyEnrollments();

    JsonVO<List<CourseEnrollmentVO>> getCourseEnrollments();

    JsonVO<List<MyScheduleVO>> getMySchedules(MyScheduleQuery query);

    JsonVO<MyScheduleVO> getMyScheduleDetail(Long id);

    JsonVO<Void> addMySchedule(MyScheduleDTO dto);

    JsonVO<Void> modifyMySchedule(MyScheduleDTO dto);

    JsonVO<Void> removeMySchedule(Long id);

    JsonVO<List<MyCustomerVO>> getMyCustomers(MyCustomerQuery query);

    JsonVO<MyCustomerVO> getMyCustomerDetail(Long id);

    JsonVO<Void> addMyCustomer(MyCustomerDTO dto);

    JsonVO<Void> modifyMyCustomer(MyCustomerDTO dto);

    JsonVO<Void> removeMyCustomer(Long id);

    @ApiOperation(value = "获取统计面板数据", notes = "返回教务系统关键统计数据，包括学生数、教师数、课程数等")
    @GetMapping("/console/statistics")
    ConsoleStatisticsVO getStatistics();

    @ApiOperation(value = "获取本月报名统计数据", notes = "返回指定月份的报名趋势和每日报名数据")
    @PostMapping("/console/month-enrollment")
    MonthEnrollmentVO getMonthEnrollment(@RequestBody MonthEnrollmentQuery query);

    @ApiOperation(value = "获取课程报名统计", notes = "返回所有课程的报名情况统计，支持条件筛选")
    @PostMapping("/console/course-enrollment")
    CourseEnrollmentVO getCourseEnrollment(@RequestBody CourseEnrollmentQuery query);

    @ApiOperation(value = "获取我的课表", notes = "返回指定用户的课程安排表")
    @PostMapping("/console/schedule")
    ScheduleVO getSchedule(@RequestBody ScheduleQuery query);

    @ApiOperation(value = "获取我的客户列表", notes = "返回负责的客户信息及跟进状态统计")
    @PostMapping("/console/customer")
    CustomerVO getCustomers(@RequestBody CustomerQuery query);
}
