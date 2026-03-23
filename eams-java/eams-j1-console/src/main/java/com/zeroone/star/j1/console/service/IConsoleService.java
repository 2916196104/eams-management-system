package com.zeroone.star.j1.console.service;

import com.zeroone.star.project.query.j1.console.*;
import com.zeroone.star.project.vo.j1.console.*;

/**
 * <p>
 * 描述：控制台服务接口
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
public interface IConsoleService {
    
    /**
     * 获取统计面板数据
     * 
     * @return 统计面板数据
     */
    ConsoleStatisticsVO getStatistics();
    
    /**
     * 获取本月报名统计数据
     * 
     * @param query 查询参数（年份、月份、课程 ID）
     * @return 本月报名统计数据
     */
    MonthEnrollmentVO getMonthEnrollment(MonthEnrollmentQuery query);
    
    /**
     * 获取课程报名统计
     * 
     * @param query 查询参数（课程名称、教师 ID、报名状态）
     * @return 课程报名统计数据
     */
    CourseEnrollmentVO getCourseEnrollment(CourseEnrollmentQuery query);
    
    /**
     * 获取我的课表
     * 
     * @param query 查询参数（用户 ID、用户类型、周次）
     * @return 个人课表数据
     */
    ScheduleVO getSchedule(ScheduleQuery query);
    
    /**
     * 获取我的客户列表
     * 
     * @param query 查询参数（客户姓名、电话、状态、意向课程）
     * @return 客户列表及统计信息
     */
    CustomerVO getCustomers(CustomerQuery query);
}
