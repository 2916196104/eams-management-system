package com.zeroone.star.project.j1;

import com.zeroone.star.project.dto.j1.customer.MyCustomerDTO;
import com.zeroone.star.project.dto.j1.schedule.MyScheduleDTO;
import com.zeroone.star.project.query.j1.console.CourseEnrollmentQuery;
import com.zeroone.star.project.query.j1.console.CustomerQuery;
import com.zeroone.star.project.query.j1.console.MonthEnrollmentQuery;
import com.zeroone.star.project.query.j1.console.ScheduleQuery;
import com.zeroone.star.project.query.j1.customer.MyCustomerQuery;
import com.zeroone.star.project.query.j1.schedule.MyScheduleQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.Console.StatisticsPanelVO;
import com.zeroone.star.project.vo.j1.console.ConsoleStatisticsVO;
import com.zeroone.star.project.vo.j1.console.CustomerVO;
import com.zeroone.star.project.vo.j1.console.MonthEnrollmentVO;
import com.zeroone.star.project.vo.j1.console.ScheduleVO;
import com.zeroone.star.project.vo.j1.customer.MyCustomerVO;
import com.zeroone.star.project.vo.j1.enrollment.CourseEnrollmentVO;
import com.zeroone.star.project.vo.j1.enrollment.MonthlyEnrollmentVO;
import com.zeroone.star.project.vo.j1.schedule.MyScheduleVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;

import java.util.List;


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

    @ApiOperation(value = "Get console statistics")
    @GetMapping("/console/statistics")
    ConsoleStatisticsVO getStatistics();

    @ApiOperation(value = "Get month enrollment")
    @PostMapping("/console/month-enrollment")
    MonthEnrollmentVO getMonthEnrollment(@RequestBody MonthEnrollmentQuery query);

    @ApiOperation(value = "Get course enrollment")
    @PostMapping("/console/course-enrollment")
    com.zeroone.star.project.vo.j1.console.CourseEnrollmentVO getCourseEnrollment(@RequestBody CourseEnrollmentQuery query);

    @ApiOperation(value = "Get schedule")
    @PostMapping("/console/schedule")
    ScheduleVO getSchedule(@RequestBody ScheduleQuery query);

    @ApiOperation(value = "Get customers")
    @PostMapping("/console/customer")
    CustomerVO getCustomers(@RequestBody CustomerQuery query);
}
