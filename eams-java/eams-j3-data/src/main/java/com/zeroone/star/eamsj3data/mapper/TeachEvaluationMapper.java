package com.zeroone.star.eamsj3data.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.eamsj3data.entity.TeachEvaluation;
import com.zeroone.star.project.dto.j3.data.TeachEvaluationDTO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;

@Mapper
public interface TeachEvaluationMapper extends BaseMapper<TeachEvaluation> {


    List<TeachEvaluationDTO> selectTeachEvaluationStats(
            @Param("startDate") LocalDate startDate,
            @Param("endDate") LocalDate endDate
    );

    Long selectTeachEvaluationStatsCount(
            @Param("startDate") LocalDate startDate,
            @Param("endDate") LocalDate endDate
    );


    List<TeachEvaluationDTO> selectTeachEvaluationStatsWithPaging(
            @Param("startDate") LocalDate startDate,
            @Param("endDate") LocalDate endDate,
            @Param("sortBy") String sortBy,
            @Param("sortOrder") String sortOrder,
            @Param("offset") long offset,
            @Param("limit") long limit
    );
}