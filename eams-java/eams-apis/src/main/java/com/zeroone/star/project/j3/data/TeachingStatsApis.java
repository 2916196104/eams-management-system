package com.zeroone.star.project.j3.data;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.data.TeachEvaluationDTO;
import com.zeroone.star.project.query.j3.data.ClassHourStatsQuery;
import com.zeroone.star.project.query.j3.data.TeachEvaluationQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.data.ClassHourStatsVO;


public interface TeachingStatsApis {
    /**
     * 分页查询学评教统计数据（包括根据时间段获取）
     * @param query 查询条件
     * @return 列表数据
     */
    public JsonVO<PageDTO<TeachEvaluationDTO>> queryTeachEvaluation(TeachEvaluationQuery query);


    /**
     * 获取课时统计数据（包括根据时间段获取）
     * @param query 查询条件
     */
    JsonVO<PageDTO<ClassHourStatsVO>> queryClassHourStats(ClassHourStatsQuery query);
}
