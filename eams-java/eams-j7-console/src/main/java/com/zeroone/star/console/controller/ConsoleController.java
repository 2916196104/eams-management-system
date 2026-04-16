package com.zeroone.star.console.controller;

import com.zeroone.star.project.dto.j7.console.CourseRegistrationDTO;
import com.zeroone.star.project.dto.j7.console.MonthlyTrendDTO;
import com.zeroone.star.project.dto.j7.console.StatisticsPanelDTO;
import com.zeroone.star.project.j7.console.ConsoleApis;
import com.zeroone.star.project.query.j7.console.CourseRegistrationQuery;
import com.zeroone.star.project.query.j7.console.MonthlyTrendQuery;
import com.zeroone.star.project.query.j7.console.StatisticsPanelQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.console.service.IConsoleService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;
import java.util.List;

/**
 * <p>
 * 描述：首页控制台接口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 不喜欢下雨天（罗涛 j7）
 * @version 1.0.0
 */
@RestController
@RequestMapping("/j7-console")
@Api(tags = "首页管理")
public class ConsoleController implements ConsoleApis {
    @Resource
    private IConsoleService consoleService;

    @ApiOperation(value = "统计面板")
    @GetMapping("/statistics-panel")
    @Override
    public JsonVO<StatisticsPanelDTO> getStatisticsPanel(StatisticsPanelQuery query) {
        StatisticsPanelDTO panel = consoleService.getStatisticsPanel(query);
        return JsonVO.success(panel);
    }

    @ApiOperation(value = "本月报名")
    @GetMapping("/monthly-trend")
    @Override
    public JsonVO<List<MonthlyTrendDTO>> getMonthlyTrend(MonthlyTrendQuery query) {
        List<MonthlyTrendDTO> trends = consoleService.getMonthlyTrend(query);
        return JsonVO.success(trends);
    }

    @ApiOperation(value = "课程报名")
    @GetMapping("/course-registration")
    @Override
    public JsonVO<List<CourseRegistrationDTO>> getCourseRegistration(CourseRegistrationQuery query) {
        List<CourseRegistrationDTO> registrations = consoleService.getCourseRegistration(query);
        return JsonVO.success(registrations);
    }
}
