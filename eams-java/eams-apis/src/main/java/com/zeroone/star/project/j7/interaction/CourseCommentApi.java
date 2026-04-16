package com.zeroone.star.project.j7.interaction;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j7.interaction.CourseCommentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j7.interaction.CourseCommentVO;
import io.swagger.annotations.Api;
import org.springframework.web.bind.annotation.RequestMapping;

/**
 * <p>
 * 描述：教师评价学生（教评学）模块 API 接口定义
 * </p>
 * <p>接口范围：获取教师点评列表</p>
 * @since 2026-03-15
 */
@RequestMapping("/teaching-evaluation/teacher-student")
@Api(tags = "教评学管理")
public interface CourseCommentApi {

    /**
     * 分页查询教师评价学生列表
     * <p>筛选条件：评价内容（模糊）、课次 ID、点评老师 ID、学生 ID、点评时间区间</p>
     * <p>分页支持：30/50/100/200 条/页（默认 30）</p>
     * <p>展示字段：序号、学员、课次标题、点评得分、点评内容、点评老师、点评时间</p>
     * @param query 查询条件（分页 + 筛选），默认页码 1，每页 30 条，支持切换 50/100/200 条
     * @return 教师点评分页列表
     */
    JsonVO<PageDTO<CourseCommentVO>> pageList(CourseCommentQuery query);
}
