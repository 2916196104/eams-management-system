package com.zeroone.star.eamsj3data.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.eamsj3data.entity.TeachEvaluation;
import com.zeroone.star.eamsj3data.mapper.TeachEvaluationMapper;
import com.zeroone.star.eamsj3data.service.TeachEvaluationService;
import com.zeroone.star.project.dto.j3.data.TeachEvaluationDTO;
import com.zeroone.star.project.query.j3.data.TeachEvaluationQuery;
import cn.hutool.core.util.StrUtil;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;


@Service
public class TeachEvaluationServiceImpl extends ServiceImpl<TeachEvaluationMapper, TeachEvaluation> implements TeachEvaluationService {
    @Override
    public Page<TeachEvaluationDTO> queryTeachEvaluation(TeachEvaluationQuery query) {
        LambdaQueryWrapper<TeachEvaluation> wrapper = new LambdaQueryWrapper<>();

        if (query.getStartDate() != null) {
            wrapper.ge(TeachEvaluation::getAddTime, query.getStartDate());
        }
        if (query.getEndDate() != null) {
            wrapper.le(TeachEvaluation::getAddTime, query.getEndDate().plusDays(1));
        }

        Page<TeachEvaluation> page = new Page<>(query.getPageIndex(), query.getPageSize());

        Page<TeachEvaluation> resultPage = this.page(page, wrapper);

        Map<Long, List<TeachEvaluation>> groupedByTeacher = resultPage.getRecords()
                .stream()
                .collect(java.util.stream.Collectors.groupingBy(TeachEvaluation::getTeacherId));

        List<TeachEvaluationDTO> dtoList = new ArrayList<>();
        for (Map.Entry<Long, List<TeachEvaluation>> entry : groupedByTeacher.entrySet()) {
            TeachEvaluationDTO dto = calculateTeacherStats(entry.getKey(), entry.getValue());
            dtoList.add(dto);
        }

        dtoList.sort((a, b) -> {
            String sortBy = StrUtil.isNotBlank(query.getSortBy()) ? query.getSortBy() : "evaluationCount";
            boolean asc = "asc".equalsIgnoreCase(query.getSortOrder());

            int cmp;
            switch (sortBy) {
                case "teacherId":
                    cmp = Long.compare(a.getTeacherId(), b.getTeacherId());
                    break;
                case "comprehensiveScore":
                    cmp = Double.compare(a.getComprehensiveScore(), b.getComprehensiveScore());
                    break;
                case "classroomAtmosphere":
                    cmp = Double.compare(a.getClassroomAtmosphere(), b.getClassroomAtmosphere());
                    break;
                case "teachingAttitude":
                    cmp = Double.compare(a.getTeachingAttitude(), b.getTeachingAttitude());
                    break;
                case "teachingEffect":
                    cmp = Double.compare(a.getTeachingEffect(), b.getTeachingEffect());
                    break;
                default:
                    cmp = Long.compare(a.getEvaluationCount(), b.getEvaluationCount());
            }

            return asc ? cmp : -cmp;
        });


        int total = dtoList.size();
        int fromIndex = Math.toIntExact(Math.min((query.getPageIndex() - 1) * query.getPageSize(), total));
        int toIndex = Math.toIntExact(Math.min(fromIndex + query.getPageSize(), total));

        List<TeachEvaluationDTO> pagedList = fromIndex < total
                ? dtoList.subList(fromIndex, toIndex)
                : new ArrayList<>();

        Page<TeachEvaluationDTO> finalPage = new Page<>(query.getPageIndex(), query.getPageSize(), total);
        finalPage.setRecords(pagedList);

        return finalPage;
    }

    /**
     * 计算教师统计数据
     */
    private TeachEvaluationDTO calculateTeacherStats(Long teacherId, List<TeachEvaluation> evaluations) {
        TeachEvaluationDTO dto = new TeachEvaluationDTO();
        dto.setTeacherId(teacherId);
        dto.setEvaluationCount((long) evaluations.size());

        double sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
        int count = 0;

        for (TeachEvaluation eval : evaluations) {
            if (eval.getScore1() != null) sum1 += eval.getScore1();
            if (eval.getScore2() != null) sum2 += eval.getScore2();
            if (eval.getScore3() != null) sum3 += eval.getScore3();
            if (eval.getScore4() != null) sum4 += eval.getScore4();
            count++;
        }

        if (count > 0) {
            dto.setClassroomAtmosphere(sum1 / count);
            dto.setTeachingAttitude(sum2 / count);
            dto.setTeachingEffect(sum3 / count);
            dto.setComprehensiveScore((sum1 + sum2 + sum3 + sum4) / (count * 4.0));
        }

        return dto;
    }
}

