package com.zeroone.star.project.j1;

import com.zeroone.star.project.dto.j1.Console.StatisticsPanelDTO;
import com.zeroone.star.project.dto.j1.customer.MyCustomerDTO;
import com.zeroone.star.project.dto.j1.schedule.MyScheduleDTO;
import com.zeroone.star.project.query.j1.customer.MyCustomerQuery;
import com.zeroone.star.project.query.j1.schedule.MyScheduleQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.Console.StatisticsPanelVO;
import com.zeroone.star.project.vo.j1.customer.MyCustomerVO;
import com.zeroone.star.project.vo.j1.enrollment.CourseEnrollmentVO;
import com.zeroone.star.project.vo.j1.enrollment.MonthlyEnrollmentVO;
import com.zeroone.star.project.vo.j1.schedule.MyScheduleVO;

import java.util.List;

/**
 * <p>
 * 描述：控制台相关 API 接口
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
public interface ConsoleApis {
    
    /**
     * 获取统计面板数据
     * @return 统计面板数据
     */
    JsonVO<StatisticsPanelVO> getStatisticsPanel();
    
    /**
     * 获取本月报名列表
     * @return 本月报名列表
     */
    JsonVO<List<MonthlyEnrollmentVO>> getMonthlyEnrollments();
    
    /**
     * 获取课程报名列表
     * @return 课程报名列表
     */
    JsonVO<List<CourseEnrollmentVO>> getCourseEnrollments();
    
    // ==================== 我的课表模块 ====================
    
    /**
     * 获取我的课表列表
     * @param query 课表查询对象
     * @return 我的课表列表
     */
    JsonVO<List<MyScheduleVO>> getMySchedules(MyScheduleQuery query);
    
    /**
     * 获取我的课表详情
     * @param id 课表 ID
     * @return 课表详情
     */
    JsonVO<MyScheduleVO> getMyScheduleDetail(Long id);
    
    /**
     * 添加我的课表
     * @param dto 课表数据对象
     * @return 操作结果
     */
    JsonVO<Void> addMySchedule(MyScheduleDTO dto);
    
    /**
     * 修改我的课表
     * @param dto 课表数据对象
     * @return 操作结果
     */
    JsonVO<Void> modifyMySchedule(MyScheduleDTO dto);
    
    /**
     * 删除我的课表
     * @param id 课表 ID
     * @return 操作结果
     */
    JsonVO<Void> removeMySchedule(Long id);
    
    // ==================== 我的客户模块 ====================
    
    /**
     * 获取我的客户列表
     * @param query 客户查询对象
     * @return 我的客户列表
     */
    JsonVO<List<MyCustomerVO>> getMyCustomers(MyCustomerQuery query);
    
    /**
     * 获取我的客户详情
     * @param id 客户 ID
     * @return 客户详情
     */
    JsonVO<MyCustomerVO> getMyCustomerDetail(Long id);
    
    /**
     * 添加我的客户
     * @param dto 客户数据对象
     * @return 操作结果
     */
    JsonVO<Void> addMyCustomer(MyCustomerDTO dto);
    
    /**
     * 修改我的客户
     * @param dto 客户数据对象
     * @return 操作结果
     */
    JsonVO<Void> modifyMyCustomer(MyCustomerDTO dto);
    
    /**
     * 删除我的客户
     * @param id 客户 ID
     * @return 操作结果
     */
    JsonVO<Void> removeMyCustomer(Long id);
}
