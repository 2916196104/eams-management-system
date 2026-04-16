package com.zeroone.star.project.j9.course;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.course.CourseSaveDTO;
import com.zeroone.star.project.query.j9.course.CourseQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j9.course.CourseDetailVO;
import com.zeroone.star.project.vo.j9.course.CourseListVO;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;

import javax.servlet.http.HttpServletResponse;
import java.util.List;

/**
 * 课程管理接口定义
 */
public interface CourseApis {

    /**
     * 获取课程列表（条件+分页）
     */
    JsonVO<PageDTO<CourseListVO>> queryCourseList(CourseQuery query);

    /**
     * 获取课程详情
     */
    JsonVO<CourseDetailVO> queryCourseDetail(
            @ApiParam(value = "课程ID", required = true) @PathVariable Long id);

    /**
     * 保存课程（新增或更新）
     */
    JsonVO<Long> addCourse(@RequestBody CourseSaveDTO dto);

    /**
     * 删除课程（支持批量删除）
     */
    JsonVO<String> removeCourse(
            @ApiParam(value = "课程ID列表", required = true) @RequestBody List<Long> ids);

    /**
     * 启/禁用课程（支持批量）
     */
    JsonVO<String> modifyCourseState(
            @ApiParam(value = "课程ID列表", required = true) @RequestBody List<Long> ids,
            @ApiParam(value = "状态：0禁用 1启用", required = true) @RequestParam Integer state);

    /**
     * 导出课程
     */
    void exportCourse(CourseQuery query, HttpServletResponse response) throws Exception;
}
