package com.zeroone.star.project.j7.interaction;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j7.interaction.TeachEvaluationQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j7.interaction.TeachEvaluationVO;
import io.swagger.annotations.Api;
import org.springframework.web.bind.annotation.RequestMapping;

/**
 * <p>
 * 描述：学生评价教师（学评教）模块 API 接口定义
 * </p>
 * <p>接口范围：获取学生点评列表</p>
 * @since 2026-03-15
 */
@RequestMapping("/teaching-evaluation/student-teacher")
@Api(tags = "学评教")
public interface TeachEvaluationApi {

    /**
     * 分页查询学生评价教师列表
     * <p>筛选条件：开始/结束日期、老师 ID、学生 ID、课次 ID</p>
     * <p>分页支持：30/50/100/200 条/页（默认 30）</p>
     * <p>展示字段：序号、学员、老师、课次标题、综合评分、课堂气氛、授课态度、教学效果、评价内容、评价时间</p>
     * @param query 查询条件（分页 + 筛选），默认页码 1，每页 30 条，支持切换 50/100/200 条
     * @return 学生点评分页列表
     */
    JsonVO<PageDTO<TeachEvaluationVO>> pageList(TeachEvaluationQuery query);
}
