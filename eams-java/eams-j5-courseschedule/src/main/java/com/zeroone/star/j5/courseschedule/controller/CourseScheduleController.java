package com.zeroone.star.j5.courseschedule.controller;

import com.zeroone.star.project.dto.j5.courseschedule.CourseStatusDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonListDTO;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.query.j5.courseschedule.CourseQuery;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j5.courseschedule.CourseScheduleApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.courseschedule.CourseScheduleVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Map;

@RestController("j5/courseschedule")
@Api(tags="课程表")
public class CourseScheduleController implements CourseScheduleApis {

    @GetMapping("/calendar")
    @ApiOperation("获取课表日历（条件）")
    @Override
    public JsonVO<List<LessonDTO>> queryList(CourseQuery condition) {
        return null;
    }

    @GetMapping("/list")
    @ApiOperation("获取课次列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<LessonListDTO>> queryPage(CourseQuery condition) {
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

    @GetMapping("/student-status/list")
    @ApiOperation("分页查询学员上课状态列表")
    @Override
    public JsonVO<PageDTO<Map<String, Object>>> list(String keyword, String status, PageQuery query) {
        return JsonVO.success(null);
    }


    @PostMapping("batch-set-status")
    @ApiOperation("批量设置课程状态")
    @Override
    public JsonVO<Integer> batchSetStatus(@ApiParam(value = "课次学员记录ID列表", required = true) @RequestBody List<Long> lessonStudentIds,
                                          @ApiParam(value = "目标状态", required = true) @RequestParam String status) {
        return JsonVO.success(0);
    }

    @PostMapping("batch-restore")
    @ApiOperation("批量还原课程进度")
    @Override
    public JsonVO<Integer> batchRestore(@ApiParam(value = "课次学员记录ID列表", required = true) @RequestBody List<Long> lessonStudentIds) {
        return JsonVO.success(0);
    }

    @PostMapping("stop")
    @ApiOperation("停课")
    @Override
    public JsonVO<Integer> stopLesson(@ApiParam(value = "课次ID列表", required = true) @RequestBody List<Long> lessonIds) {
        return JsonVO.success(0);
    }

    @PostMapping("resume")
    @ApiOperation("复课")
    @Override
    public JsonVO<Integer> resumeLesson(@ApiParam(value = "课次ID列表", required = true) @RequestBody List<Long> lessonIds) {
        return JsonVO.success(0);
    }

}
