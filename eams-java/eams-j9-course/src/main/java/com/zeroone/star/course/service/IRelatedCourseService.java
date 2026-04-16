package com.zeroone.star.course.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.course.CourseDTO;
import com.zeroone.star.project.dto.j9.course.CourseLinkDTO;
import com.zeroone.star.project.query.j9.course.CourseLinkPageQuery;

import java.util.List;

/**
 * 关联课程服务接口
 */
public interface IRelatedCourseService {

    /**
     * 获取关联课程列表（条件+分页）
     */
    PageDTO<CourseLinkDTO> listPage(CourseLinkPageQuery condition);

    /**
     * 添加关联课程（支持多选）
     */
    Long saveCourseLink(Long courseId, List<Long> linkedCourseIds);

    /**
     * 移除关联课程（支持多选）
     */
    List<Long> removeCourseLink(Long courseId, List<Long> linkedCourseIds);
}
