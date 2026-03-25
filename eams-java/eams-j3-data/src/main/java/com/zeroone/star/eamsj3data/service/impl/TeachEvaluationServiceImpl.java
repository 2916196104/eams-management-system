package com.zeroone.star.eamsj3data.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.eamsj3data.entity.TeachEvaluation;
import com.zeroone.star.eamsj3data.mapper.TeachEvaluationMapper;
import com.zeroone.star.eamsj3data.service.TeachEvaluationService;
import com.zeroone.star.project.dto.j3.data.TeachEvaluationDTO;
import com.zeroone.star.project.query.j3.data.TeachEvaluationQuery;
import cn.hutool.core.util.StrUtil;
import org.springframework.stereotype.Service;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;

@Service
public class TeachEvaluationServiceImpl extends ServiceImpl<TeachEvaluationMapper, TeachEvaluation> implements TeachEvaluationService {

    @Override
    public Page<TeachEvaluationDTO> queryTeachEvaluation(TeachEvaluationQuery query) {
        LocalDate startDate = query.getStartDate();
        LocalDate endDate = query.getEndDate() != null ? query.getEndDate().plusDays(1) : null;

        // 1. 查询总记录数
        Long total = baseMapper.selectTeachEvaluationStatsCount(startDate, endDate);

        // 2. 查询当前页的数据
        List<TeachEvaluationDTO> pagedList = baseMapper.selectTeachEvaluationStatsWithPaging(
                startDate,
                endDate,
                getValidatedSortField(query.getSortBy()),
                query.getSortOrder(),
                (query.getPageIndex() - 1) * query.getPageSize(),
                query.getPageSize()
        );

        // 3. 构造并返回分页结果
        Page<TeachEvaluationDTO> finalPage = new Page<>(query.getPageIndex(), query.getPageSize(), total);
        finalPage.setRecords(pagedList);

        return finalPage;
    }

    private String getValidatedSortField(String sortBy) {
        if (StrUtil.isBlank(sortBy)) {
            return "evaluationCount";
        }
        // 白名单，只允许特定的字段进行排序
        switch (sortBy.toLowerCase()) {
            case "teacherid":
                return "teacherId";
            case "comprehensivescore":
                return "comprehensiveScore";
            case "classroomatmosphere":
                return "classroomAtmosphere";
            case "teachingattitude":
                return "teachingAttitude";
            case "teachingeffect":
                return "teachingEffect";
            case "evaluationcount":
            default:
                return "evaluationCount";
        }
    }
}