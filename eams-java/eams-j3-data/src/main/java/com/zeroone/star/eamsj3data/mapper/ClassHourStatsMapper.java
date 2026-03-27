package com.zeroone.star.eamsj3data.mapper;


import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.vo.j3.data.ClassHourStatsVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

import java.time.LocalDate;

@Mapper
public interface ClassHourStatsMapper {
    Page<ClassHourStatsVO> selectClassHourStats(
            Page<ClassHourStatsVO> page,
            @Param("startDate") LocalDate startDate,
            @Param("endDate") LocalDate endDate
    );

    Long selectClassHourStatsCount(
            @Param("startDate") LocalDate startDate,
            @Param("endDate") LocalDate endDate
    );
}
