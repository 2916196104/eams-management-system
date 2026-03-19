package com.zeroone.star.j5.courseschedule.controller;

import com.zeroone.star.project.dto.j5.coursrschedule.CourseStatusDTO;
import com.zeroone.star.project.dto.j5.coursrschedule.LessonDTO;
import com.zeroone.star.project.dto.j5.coursrschedule.LessonListDTO;
import com.zeroone.star.project.query.j5.courseschedule.LessonQuery;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j5.courseschedule.CourseScheduleApis;
import com.zeroone.star.project.query.j5.couserUAndD.UpdateCourseQuery;
import com.zeroone.star.project.query.j5.couserUAndD.UpdateCoursesQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.courseschedule.CourseScheduleVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController("j5/courseschedule")
@Api(tags="课程表")
public class CourseScheduleControoler implements CourseScheduleApis {

    @GetMapping("/calendar")
    @ApiOperation("获取课表日历（条件）")
    @Override
    public JsonVO<List<LessonDTO>> queryList(LessonQuery condition) {
        return null;
    }

    @GetMapping("/list")
    @ApiOperation("获取课次列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<LessonListDTO>> queryPage(LessonQuery condition) {
        return null;
    }

    @GetMapping("/detail")
    @ApiOperation("获取课次详情")
    @Override
    public JsonVO<List<LessonListDTO>> queryNameList(Long id) {
        return null;
    }



    @PostMapping("/repeat-schedule")
    @ApiOperation("重复排课")
    @Override
    public JsonVO<String> repeatSchedule(CourseScheduleVO courseScheduleVO) {
        return null;
    }

    @PostMapping("/free-schedule")
    @ApiOperation("自由排课")
    @Override
    public JsonVO<String> freeSchedule(CourseScheduleVO courseScheduleVO) {
        return null;
    }

    @PostMapping("/switch-schedule")
    @ApiOperation("预约课程开关")
    @Override
    public JsonVO<String> switchSchedule(CourseStatusDTO courseStatusDto) {
        return null;
    }

    @PostMapping("/UpdateCourse")
    @ApiOperation("修改课次")
    @Override
    public JsonVO<String> updateCourse(UpdateCourseQuery updateCourseQuery) {
        return null;
    }

    @PostMapping("/updateCourses")
    @ApiOperation("批量修改课次")
    @Override
    public JsonVO<String> updateCourses(List<UpdateCoursesQuery> updateCoursesQueries) {
        return null;
    }

    @PostMapping("/deleteCourses")
    @ApiOperation("删除课次")
    @Override
    public JsonVO<String> deleteCourses(List<Long> ids) {
        return null;
    }
}
