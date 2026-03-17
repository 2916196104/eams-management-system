package com.zeroone.star.project.j3.teachingstats;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.teachingstats.ClassHourStatsDTO;
import com.zeroone.star.project.dto.j3.teachingstats.TeachEvaluationDTO;
import com.zeroone.star.project.query.j3.teachingstats.ClassHourStatsQuery;
import com.zeroone.star.project.query.j3.teachingstats.TeachEvaluationQuery;


public interface TeachingStatsApis {
    /**
     * 分页查询学评教统计数据（包括根据时间段获取）
     * @param query 查询条件
     * @return 列表数据
     */
    PageDTO<TeachEvaluationDTO> queryTeachEvaluation(TeachEvaluationQuery query);


    /**
     * 根据evaluationCount，comprehensiveScore，classroomAtmosphere，teachingAttitude，teachingEffect
     * 进行升序或者降序排序
     */
    PageDTO<TeachEvaluationDTO> queryTeachEvaluationBySort(TeachEvaluationQuery query);

    /**
     * 获取课时统计数据（包括根据时间段获取）
     * @param query 查询条件
     */
    PageDTO<ClassHourStatsDTO> queryClassHourStats(ClassHourStatsQuery query);
}
