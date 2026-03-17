package com.zeroone.star.eamsj3class.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.AddCourseDTO;
import com.zeroone.star.project.j3.course.CourseApis;
import com.zeroone.star.project.query.j3.course.CourseListQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.course.CourseDetailVO;
import com.zeroone.star.project.vo.j3.course.CourseListVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * <p>
 * 描述：课程controller
 * </p>
 *
 * @author heavydrink
 * @version 1.0.0
 */
@RestController
@RequestMapping("/course")
@Api(tags = "课程管理")
public class CourseController implements CourseApis {
    @GetMapping("/query-courses-list")
    @Override
    @ApiOperation("获取课程列表（条件 + 分页）")
    public JsonVO<PageDTO<CourseListVO>> queryCourseList(CourseListQuery courseListQuery) {
        return null;
    }

    @GetMapping("/query-one-course/{courseId}")
    @Override
    @ApiOperation("获取课程详情")
    public JsonVO<CourseDetailVO> queryCourseDetail(@PathVariable Long courseId) {
        return null;
    }

    @PostMapping("/add-course")
    @Override
    @ApiOperation("保存课程")
    public JsonVO<String> addCourse(@RequestBody AddCourseDTO addCourseDTO) {
        return null;
    }

    @DeleteMapping("/delete-courses")
    @Override
    @ApiOperation("删除课程（支持批量删除）")
    public JsonVO<String> deleteCourses(@RequestBody List<String> courseIds) {
        return null;
    }
}
