package com.zeroone.star.console.service;

import com.zeroone.star.project.dto.j7.console.CourseRegistrationDTO;
import com.zeroone.star.project.dto.j7.console.MonthlyTrendDTO;
import com.zeroone.star.project.dto.j7.console.StatisticsPanelDTO;
import com.zeroone.star.project.query.j7.console.CourseRegistrationQuery;
import com.zeroone.star.project.query.j7.console.MonthlyTrendQuery;
import com.zeroone.star.project.query.j7.console.StatisticsPanelQuery;

import java.util.List;

/**
 * <p>
 * 描述：首页控制台服务接口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 不喜欢下雨天（罗涛 j7）
 * @version 1.0.0
 */
public interface IConsoleService {
    /**
     * 获取统计面板核心指标
     * @param query 查询参数
     * @return 统计面板核心指标
     */
    StatisticsPanelDTO getStatisticsPanel(StatisticsPanelQuery query);

    /**
     * 获取本月报名走势数据
     * @param query 查询参数
     * @return 本月报名数据列表
     */
    List<MonthlyTrendDTO> getMonthlyTrend(MonthlyTrendQuery query);

    /**
     * 获取课程报名Top5数据
     * @param query 查询参数
     * @return 课程报名数据列表
     */
    List<CourseRegistrationDTO> getCourseRegistration(CourseRegistrationQuery query);
}
