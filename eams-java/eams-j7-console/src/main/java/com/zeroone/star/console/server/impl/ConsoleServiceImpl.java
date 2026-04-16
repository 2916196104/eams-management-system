package com.zeroone.star.console.server.impl;

import com.zeroone.star.project.dto.j7.console.CourseRegistrationDTO;
import com.zeroone.star.project.dto.j7.console.MonthlyTrendDTO;
import com.zeroone.star.project.dto.j7.console.StatisticsPanelDTO;
import com.zeroone.star.project.query.j7.console.CourseRegistrationQuery;
import com.zeroone.star.project.query.j7.console.MonthlyTrendQuery;
import com.zeroone.star.project.query.j7.console.StatisticsPanelQuery;
import com.zeroone.star.console.mapper.ConsoleMapper;
import com.zeroone.star.console.server.IConsoleService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.Collections;
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
        return null;
    }

    @Override
    public List<MonthlyTrendDTO> getMonthlyTrend(MonthlyTrendQuery query) {
        return Collections.emptyList();
    }

    @Override
    public List<CourseRegistrationDTO> getCourseRegistration(CourseRegistrationQuery query) {
        return Collections.emptyList();
    }
}
