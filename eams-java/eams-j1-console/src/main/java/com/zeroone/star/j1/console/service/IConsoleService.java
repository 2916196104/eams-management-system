package com.zeroone.star.j1.console.service;

import com.zeroone.star.project.query.j1.console.*;
import com.zeroone.star.project.vo.j1.console.*;

import java.util.List;

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
     * @param query 查询参数（年份、月份）
     * @return 本月报名统计数据
     */
    MonthEnrollmentVO getMonthEnrollment(MonthEnrollmentQuery query);
    
    /**
     * 获取课程报名金额排行（前5）
     * 
     * @return 课程报名金额排行列表
     */
    List<CourseEnrollmentRankVO> getCourseEnrollmentRank();
    
    /**
     * 获取课表日历数据
     *
     * @param query 查询参数
     * @return 课表日历数据
     */
    TimetableCalendarVO getTimetableCalendar(TimetableCalendarQuery query);

    /**
     * 获取我的客户列表（分页）
     *
     * @param query 查询参数
     * @return 我的客户分页数据
     */
    MyCustomerVO getMyCustomerList(MyCustomerQuery query);
}
