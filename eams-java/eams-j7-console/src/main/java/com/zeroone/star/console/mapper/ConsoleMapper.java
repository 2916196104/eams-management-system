package com.zeroone.star.console.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.j7.console.CourseRegistrationDTO;
import com.zeroone.star.project.dto.j7.console.MonthlyTrendDTO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.util.List;

/**
 * <p>
 * 描述：控制台数据访问接口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 不喜欢下雨天（罗涛 j7）
 * @version 1.0.0
 */
@Mapper
public interface ConsoleMapper extends BaseMapper {
    Long countStudents();

    Long countTeachers();

    Long countLessons();

    BigDecimal sumMonthlyRevenue(@Param("startDate") LocalDate startDate, @Param("endDate") LocalDate endDate);

    List<MonthlyTrendDTO> selectDailyRegistrationTrend(@Param("startDate") LocalDate startDate, @Param("endDate") LocalDate endDate);

    List<CourseRegistrationDTO> selectTop5CourseRegistration();
}
