package com.zeroone.star.j5.courseschedule.controller;

import com.zeroone.star.j5.courseschedule.service.CourseStudentService;
import com.zeroone.star.project.dto.j5.courseschedule.*;
import com.zeroone.star.project.query.j5.courseschedule.*;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j5.courseschedule.CourseScheduleApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.courseschedule.CourseDetailVO;
import com.zeroone.star.project.vo.j5.courseschedule.CourseListVO;
import com.zeroone.star.project.vo.j5.courseschedule.EvaluationVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;
import java.util.List;
import java.util.Map;

@Slf4j
@RestController
@RequestMapping("/j5/courseschedule")
@Api(tags="课程表")
public class CourseScheduleController implements CourseScheduleApis {

    @Resource
    private CourseStudentService courseStudentService;

    @GetMapping("/calendar")
    @ApiOperation("获取课表日历（条件）")
    @Override
    public JsonVO<List<LessonDTO>> queryCalendar(CourseQuery condition) {
        log.info("查询课表日历，参数：{}", condition);
        return null;
    }

    @GetMapping("/list")
    @ApiOperation("获取课次列表（条件 + 分页）")
    @Override
    public JsonVO<PageDTO<CourseListVO>> queryCourseList(CourseListQuery courseListQuery) {
        log.info("查询课次列表，参数：{}", courseListQuery);
        return null;
    }

    @GetMapping("/detail/{id}")
    @ApiOperation("获取课次详情")
    @Override
    public JsonVO<CourseDetailVO> queryCourseDetail(Long id) {
        return null;
    }



    @PostMapping("/repeat-schedule")
    @ApiOperation("重复排课")
    @Override
    public JsonVO<String> repeatSchedule(@RequestBody @Validated CourseScheduleDTO courseScheduleVO) {
        log.info("重复排课，参数：{}", courseScheduleVO);

        return null;
    }

    @PostMapping("/free-schedule")
    @ApiOperation("自由排课")
    @Override
    public JsonVO<String> freeSchedule(@RequestBody @Validated CourseScheduleDTO courseScheduleVO) {
        log.info("自由排课，参数：{}", courseScheduleVO);
        return null;
    }


    @PutMapping("/update-course")
    @ApiOperation("修改课次")
    @Override
    public JsonVO<String> updateCourse(@RequestBody @Validated UpdateCourseDTO updateCourseDTO) {
        log.info("修改课次，参数：{}", updateCourseDTO);
        Boolean result = courseStudentService.updateCourse(updateCourseDTO);
        return result ? JsonVO.success("修改成功") : JsonVO.fail("修改失败");
    }

    @PutMapping("/batch-update-courses")
    @ApiOperation("批量修改课次")
    @Override
    public JsonVO<String> updateCourses(@RequestBody @Validated BatchUpdateCourseDTO batchUpdateCourseDTO) {
        log.info("批量修改课次，参数：{}", batchUpdateCourseDTO);
        Boolean result = courseStudentService.updateCourses(batchUpdateCourseDTO);
        return result ? JsonVO.success("修改成功") : JsonVO.fail("课次状态异常，只能选中进行中的课程");
    }

    @DeleteMapping("/delete-courses")
    @ApiOperation("删除课次")
    @Override
    public JsonVO<String> deleteCourses(@RequestBody List<Long> ids) {
        log.info("删除课次，参数：{}", ids);
        Boolean result = courseStudentService.deleteCourses(ids);
        return result ? JsonVO.success("删除成功") : JsonVO.fail("删除失败");
    }

    @PostMapping("/switch-schedule")
    @ApiOperation("预约课程开关")
    @Override
    public JsonVO<String> switchSchedule(@RequestBody @Validated CourseAppointStatusDTO courseAppointStatusDto) {
        log.info("预约课程开关，参数：{}", courseAppointStatusDto);
        return null;
    }

    @GetMapping("/student-status/list")
    @ApiOperation("分页查询学员上课状态列表")
    @Override
    public JsonVO<PageDTO<Map<String, Object>>> queryStudentsStatusList(StudentStatusQuery studentStatusQuery) {
        return JsonVO.success(null);
    }


    @PostMapping("/batch-set-status")
    @ApiOperation("设置学员上课状态")
    @Override
    public JsonVO<Integer> batchSetStatus(@RequestBody @Validated SetStudentsStatusDTO setStudentsStatusDTO) {
        log.info("设置学员上课状态，参数：{}", setStudentsStatusDTO);
        return JsonVO.success(0);
    }

    @PostMapping("/batch-restore")
    @ApiOperation("批量还原课程进度")
    @Override
    public JsonVO<Integer> batchRestore(@RequestBody @Validated RollBackDTO rollBackDTO) {
        log.info("批量还原课程进度，参数：{}", rollBackDTO);
        return JsonVO.success(0);
    }


    @PutMapping("/resume")
    @ApiOperation("停/复课")
    @Override
    public JsonVO<Integer> resumeLesson(@RequestBody @Validated CoursePauseResumeDTO coursePauseResumeDTO) {
        log.info("停/复课，参数：{}", coursePauseResumeDTO);
        return JsonVO.success(0);
    }

    @Override
    @ApiOperation("添加随课生")
    @PostMapping("/course-student")
    public JsonVO<Long> saveCourseStudent(@RequestBody CourseStudentDTO courseStudentDTO) {
        return null;
    }

    @Override
    @GetMapping("/evaluation/list")
    @ApiOperation("获取课后点评列表（条件 + 分页）")
    public JsonVO<PageDTO<EvaluationVO>> queryPage(EvaluationQuery condition) {
        log.info("查询课后点评列表，参数：{}", condition);
        return null;
    }

    @PostMapping("/evaluation")
    @Override
    @ApiOperation("保存点评")
    public JsonVO<Long> saveEvaluation(@RequestBody @Validated EvaluationDTO evaluationDTO) {
        log.info("保存点评，参数：{}", evaluationDTO);
        return null;
    }


}
