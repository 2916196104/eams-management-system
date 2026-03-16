package com.zeroone.star.project.j3.course;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.AddCourseDTO;
import com.zeroone.star.project.query.j3.course.CourseListQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.course.CourseDetailVO;
import com.zeroone.star.project.vo.j3.course.CourseListVO;


import java.util.List;

/**
 * <p>
 * 描述：课程模块Api
 * </p>
 *
 * @author heavydrink
 * @version 1.0.0
 */
public interface CourseApis {
    // 1. 获取课程列表（条件 + 分页）
    JsonVO<PageDTO<CourseListVO>> queryCourseList(CourseListQuery courseListQuery);

    //2. 获取课程详情
    JsonVO<CourseDetailVO> queryCourseDetail(Long courseId);

    //3. 保存课程
    JsonVO<String> addCourse(AddCourseDTO addCourseDTO);

    //4. 删除课程（支持批量删除）
    JsonVO<String> deleteCourses(List<String> courseIds);
}
