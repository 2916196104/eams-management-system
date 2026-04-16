package com.zeroone.star.j7.interaction.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j7.interaction.TeachEvaluationQuery;
import com.zeroone.star.project.vo.j7.interaction.TeachEvaluationVO;

/**
 * 学生评价教师Service接口
 * 贴合数据库结构 + 原型图筛选/展示逻辑
 */
public interface TeachEvaluationService {

    /**
     * 分页查询学生评价教师列表
     * @param query 筛选条件（老师ID/学生ID/课次ID/评价时间区间 + 分页）
     * @return 分页后的评价列表（含原型图所有展示字段）
     */
    PageDTO<TeachEvaluationVO> pageList(TeachEvaluationQuery query);
}