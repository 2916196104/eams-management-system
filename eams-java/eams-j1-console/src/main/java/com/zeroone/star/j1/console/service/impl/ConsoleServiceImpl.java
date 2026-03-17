package com.zeroone.star.j1.console.service.impl;

import com.zeroone.star.j1.console.service.IConsoleService;
import com.zeroone.star.project.query.j1.console.*;
import com.zeroone.star.project.vo.j1.console.*;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

/**
 * <p>
 * 描述：控制台服务实现类
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@Service
public class ConsoleServiceImpl implements IConsoleService {
    
    @Override
    public ConsoleStatisticsVO getStatistics() {
        // TODO: 待实现，从数据库查询真实数据
        ConsoleStatisticsVO vo = new ConsoleStatisticsVO();
        vo.setTotalStudents(1200);
        vo.setTotalTeachers(85);
        vo.setTotalCourses(156);
        vo.setTotalClasses(42);
        vo.setTodayAttendanceRate(96.5);
        vo.setMonthEnrollments(328);
        vo.setPendingTasks(15);
        return vo;
    }
    
    @Override
    public MonthEnrollmentVO getMonthEnrollment(MonthEnrollmentQuery query) {
        // TODO: 待实现，从数据库查询真实数据
        MonthEnrollmentVO vo = new MonthEnrollmentVO();
        vo.setMonth(query.getYear() + "-" + String.format("%02d", query.getMonth()));
        vo.setTotalEnrollments(328);
        vo.setTargetCompletionRate(82.5);
        
        // 模拟每日报名数据
        List<MonthEnrollmentVO.DailyEnrollmentData> dailyData = new ArrayList<>();
        for (int i = 1; i <= 15; i++) {
            MonthEnrollmentVO.DailyEnrollmentData data = new MonthEnrollmentVO.DailyEnrollmentData();
            data.setDate("2024-03-" + String.format("%02d", i));
            data.setCount((int)(Math.random() * 30) + 10);
            dailyData.add(data);
        }
        vo.setDailyData(dailyData);
        
        return vo;
    }
    
    @Override
    public CourseEnrollmentVO getCourseEnrollment(CourseEnrollmentQuery query) {
        // TODO: 待实现，从数据库查询真实数据
        CourseEnrollmentVO vo = new CourseEnrollmentVO();
        vo.setTotalCourses(156);
        vo.setEnrollingCourses(42);
        vo.setFullCourses(28);
        
        // 模拟课程报名列表
        List<CourseEnrollmentVO.CourseEnrollmentItem> courseList = new ArrayList<>();
        CourseEnrollmentVO.CourseEnrollmentItem item1 = new CourseEnrollmentVO.CourseEnrollmentItem();
        item1.setCourseId(1001);
        item1.setCourseName("Java 高级编程");
        item1.setTeacherName("张老师");
        item1.setEnrolledCount(45);
        item1.setTotalCapacity(60);
        item1.setRemainingSlots(15);
        item1.setEnrollmentStatus(1);
        courseList.add(item1);
        
        CourseEnrollmentVO.CourseEnrollmentItem item2 = new CourseEnrollmentVO.CourseEnrollmentItem();
        item2.setCourseId(1002);
        item2.setCourseName("Python 数据分析");
        item2.setTeacherName("李老师");
        item2.setEnrolledCount(60);
        item2.setTotalCapacity(60);
        item2.setRemainingSlots(0);
        item2.setEnrollmentStatus(2);
        courseList.add(item2);
        
        vo.setCourseList(courseList);
        
        return vo;
    }
    
    @Override
    public ScheduleVO getSchedule(ScheduleQuery query) {
        // TODO: 待实现，从数据库查询真实数据
        ScheduleVO vo = new ScheduleVO();
        vo.setUserId(query.getUserId());
        vo.setUserType(query.getUserType());
        vo.setWeek(query.getWeek() != null ? query.getWeek() : 5);
        
        // 模拟课表数据
        List<ScheduleVO.ScheduleItem> scheduleList = new ArrayList<>();
        ScheduleVO.ScheduleItem item1 = new ScheduleVO.ScheduleItem();
        item1.setScheduleId(5001);
        item1.setCourseId(1001);
        item1.setCourseName("Java 高级编程");
        item1.setTeacherName("张老师");
        item1.setClassroom("教学楼 A-301");
        item1.setDayOfWeek(1);
        item1.setPeriod(1);
        item1.setStartTime("08:00");
        item1.setEndTime("09:40");
        scheduleList.add(item1);
        
        ScheduleVO.ScheduleItem item2 = new ScheduleVO.ScheduleItem();
        item2.setScheduleId(5002);
        item2.setCourseId(1002);
        item2.setCourseName("数据库原理");
        item2.setTeacherName("王老师");
        item2.setClassroom("教学楼 B-205");
        item2.setDayOfWeek(2);
        item2.setPeriod(3);
        item2.setStartTime("14:00");
        item2.setEndTime("15:40");
        scheduleList.add(item2);
        
        vo.setScheduleList(scheduleList);
        
        return vo;
    }
    
    @Override
    public CustomerVO getCustomers(CustomerQuery query) {
        // TODO: 待实现，从数据库查询真实数据
        CustomerVO vo = new CustomerVO();
        vo.setTotalCustomers(256);
        vo.setPotentialCustomers(85);
        vo.setFollowingCustomers(120);
        vo.setEnrolledCustomers(48);
        
        // 模拟客户列表
        List<CustomerVO.CustomerItem> customerList = new ArrayList<>();
        CustomerVO.CustomerItem item1 = new CustomerVO.CustomerItem();
        item1.setCustomerId(3001);
        item1.setCustomerName("李明");
        item1.setPhone("13800138000");
        item1.setWechat("liming2024");
        item1.setInterestedCourse("Java 高级编程");
        item1.setStatus(1);
        item1.setLastContactTime("2024-03-15 14:30:00");
        customerList.add(item1);
        
        CustomerVO.CustomerItem item2 = new CustomerVO.CustomerItem();
        item2.setCustomerId(3002);
        item2.setCustomerName("王芳");
        item2.setPhone("13900139000");
        item2.setWechat("wangfang888");
        item2.setInterestedCourse("Python 数据分析");
        item2.setStatus(0);
        item2.setLastContactTime("2024-03-14 10:20:00");
        customerList.add(item2);
        
        vo.setCustomerList(customerList);
        
        return vo;
    }
}
