package com.zeroone.star.j7.interaction.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j7.interaction.CourseCommentQuery;
import com.zeroone.star.project.vo.j7.interaction.CourseCommentVO;

/**
 * 教评学-教师评价学生 服务接口
 * 核心：分页查询教师对学生的点评数据
 */
public interface CourseCommentService {

    /**
     * 分页查询教师点评列表
     * @param query 分页+条件查询参数
     * @return 分页后的点评VO列表
     */
    PageDTO<CourseCommentVO> pageList(CourseCommentQuery query);
}