package com.zeroone.star.project.j1;

import com.zeroone.star.project.dto.j1.console.*;
import com.zeroone.star.project.query.j1.console.*;
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
 * @author hxb
 * @version 1.0.0
 */
@Api(tags = "控制台管理")
public interface ConsoleApis {
    
    /**
     * 获取统计面板数据
     * 
     * @return 统计面板数据
     */
    @ApiOperation(value = "获取统计面板数据", notes = "返回教务系统关键统计数据，包括学生数、教师数、课程数等")
    @GetMapping("/console/statistics")
    ConsoleStatisticsVO getStatistics();
    
    /**
     * 获取本月报名统计数据
     * 
     * @param query 查询参数（年份、月份、课程 ID）
     * @return 本月报名统计数据
     */
    @ApiOperation(value = "获取本月报名统计数据", notes = "返回指定月份的报名趋势和每日报名数据")
    @PostMapping("/console/month-enrollment")
    MonthEnrollmentVO getMonthEnrollment(@RequestBody MonthEnrollmentQuery query);
    
    /**
     * 获取课程报名统计
     * 
     * @param query 查询参数（课程名称、教师 ID、报名状态）
     * @return 课程报名统计数据
     */
    @ApiOperation(value = "获取课程报名统计", notes = "返回所有课程的报名情况统计，支持条件筛选")
    @PostMapping("/console/course-enrollment")
    CourseEnrollmentVO getCourseEnrollment(@RequestBody CourseEnrollmentQuery query);
    
    /**
     * 获取我的课表
     * 
     * @param query 查询参数（用户 ID、用户类型、周次）
     * @return 个人课表数据
     */
    @ApiOperation(value = "获取我的课表", notes = "返回指定用户的课程安排表")
    @PostMapping("/console/schedule")
    ScheduleVO getSchedule(@RequestBody ScheduleQuery query);
    
    /**
     * 获取我的客户列表
     * 
     * @param query 查询参数（客户姓名、电话、状态、意向课程）
     * @return 客户列表及统计信息
     */
    @ApiOperation(value = "获取我的客户列表", notes = "返回负责的客户信息及跟进状态统计")
    @PostMapping("/console/customer")
    CustomerVO getCustomers(@RequestBody CustomerQuery query);
}
