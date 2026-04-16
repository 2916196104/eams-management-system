package com.zeroone.star.project.j9.course;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.course.CourseLinkDTO;
import com.zeroone.star.project.query.j9.course.CourseLinkPageQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.List;

/**
 * 关联课程管理接口定义
 */
public interface RelatedCourseApis {

    /**
     * 获取关联课程列表（条件+分页）
     */
    JsonVO<PageDTO<CourseLinkDTO>> queryPage(CourseLinkPageQuery condition);

    /**
     * 添加关联课程（支持多选）
     */
    JsonVO<Long> addCourseLink(
            @ApiParam(value = "课程ID", required = true) @RequestParam("courseId") Long courseId,
            @ApiParam(value = "关联课程ID列表", required = true) @RequestParam("linkedCourseIds") List<Long> linkedCourseIds);

    /**
     * 移除关联课程（支持多选）
     */
    JsonVO<?> removeCourseLink(
            @ApiParam(value = "课程ID", required = true) @RequestParam("courseId") Long courseId,
            @ApiParam(value = "关联课程ID列表", required = true) @RequestParam("linkedCourseIds") List<Long> linkedCourseIds);
}
