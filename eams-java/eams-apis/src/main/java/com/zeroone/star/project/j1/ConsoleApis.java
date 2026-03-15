package com.zeroone.star.project.j1;

import com.zeroone.star.project.dto.j1.Console.StatisticsPanelDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.Console.StatisticsPanelVO;
import com.zeroone.star.project.vo.j1.enrollment.CourseEnrollmentVO;
import com.zeroone.star.project.vo.j1.enrollment.MonthlyEnrollmentVO;

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
}
