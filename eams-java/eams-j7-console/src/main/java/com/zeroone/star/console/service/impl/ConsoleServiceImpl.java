package com.zeroone.star.console.service.impl;

import com.zeroone.star.project.dto.j7.console.CourseRegistrationDTO;
import com.zeroone.star.project.dto.j7.console.MonthlyTrendDTO;
import com.zeroone.star.project.dto.j7.console.StatisticsPanelDTO;
import com.zeroone.star.project.query.j7.console.CourseRegistrationQuery;
import com.zeroone.star.project.query.j7.console.MonthlyTrendQuery;
import com.zeroone.star.project.query.j7.console.StatisticsPanelQuery;
import com.zeroone.star.console.mapper.ConsoleMapper;
import com.zeroone.star.console.service.IConsoleService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.YearMonth;
import java.util.List;

/**
 * <p>
 * 描述：首页控制台服务实现类
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 不喜欢下雨天（罗涛 j7）
 * @version 1.0.0
 */
@Service
public class ConsoleServiceImpl implements IConsoleService {

    @Resource
    private ConsoleMapper consoleMapper;

    @Override
    public StatisticsPanelDTO getStatisticsPanel(StatisticsPanelQuery query) {
        StatisticsPanelDTO dto = new StatisticsPanelDTO();
        // 统计学员人数（未删除的）
        dto.setStudentCount(consoleMapper.countStudents());
        // 统计内部师资人数
        dto.setTeacherCount(consoleMapper.countTeachers());
        // 统计总课次（未删除的）
        dto.setTotalLessonCount(consoleMapper.countLessons());
        // 统计本月报名金额
        YearMonth currentMonth = YearMonth.now();
        LocalDate startDate = currentMonth.atDay(1);
        LocalDate endDate = currentMonth.atEndOfMonth();
        BigDecimal monthlyRevenue = consoleMapper.sumMonthlyRevenue(startDate, endDate);
        dto.setMonthlyRevenue(monthlyRevenue != null ? monthlyRevenue : BigDecimal.ZERO);
        return dto;
    }

    @Override
    public List<MonthlyTrendDTO> getMonthlyTrend(MonthlyTrendQuery query) {
        LocalDate startDate = query.getStartDate();
        LocalDate endDate = query.getEndDate();

        if (startDate == null || endDate == null) {
            YearMonth currentMonth = YearMonth.now();
            startDate = currentMonth.atDay(1);
            endDate = currentMonth.atEndOfMonth();
        }

        return consoleMapper.selectDailyRegistrationTrend(startDate, endDate);
    }


    @Override
    public List<CourseRegistrationDTO> getCourseRegistration(CourseRegistrationQuery query) {
        // 查询课程报名TOP5
        return consoleMapper.selectTop5CourseRegistration();
    }
}
