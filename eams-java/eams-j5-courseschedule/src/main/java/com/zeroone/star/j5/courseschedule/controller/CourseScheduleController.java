package com.zeroone.star.j5.courseschedule.controller;

import com.zeroone.star.j5.courseschedule.service.*;
import com.zeroone.star.project.dto.j5.courseschedule.*;
import com.zeroone.star.project.query.j5.courseschedule.*;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j5.courseschedule.CourseScheduleApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.courseschedule.*;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.apache.ibatis.annotations.Param;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;
import java.util.List;
import java.util.Map;

@Slf4j
@RestController
@RequestMapping("/j5-course-schedule")
@EnableDiscoveryClient
@RequiredArgsConstructor
@Api(tags="课程表")
public class CourseScheduleController implements CourseScheduleApis {

    @Resource
    private CourseStudentService courseStudentService;
    @Resource
    IEvaluationService evaluationService;

    @Resource
    ICasualStudentService casualStudentService;
    private final ILessonService ilessonService;

    @Resource
    private ILessonStudentService lessonStudentService;

    private final ILessonScheduleService lessonSchduleService;


    @GetMapping("/calendar")
    @ApiOperation("获取课表日历（条件）")
    @Override
    public JsonVO<List<LessonCalendarVO>> queryCalendar(LessonQueryDTO query) {
        List<LessonCalendarVO> list = ilessonService.calendar(query);
        return JsonVO.success(list);
    }

    @GetMapping("/list")
    @ApiOperation("获取课次列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<LessonListVO>> queryCourseList(LessonQueryDTO query) {
        PageDTO<LessonListVO> page = ilessonService.pageList(query);
        return JsonVO.success(page);
    }

    @GetMapping("/detail/{id}")
    @ApiOperation("获取课次详情")
    @Override
    public JsonVO<LessonDetailVO> queryCourseDetail(@PathVariable Long id) {
        LessonDetailVO detail = ilessonService.detail(id);
        return JsonVO.success(detail);
    }




    @PostMapping("/repeat-schedule")
    @ApiOperation("重复排课")
    @Override
    public JsonVO<String> repeatSchedule(@Param("courseScheduleDto")CourseScheduleDTO courseScheduleVO) {
        log.info("参数：{}",courseScheduleVO);
        return lessonSchduleService.reapteSchedule(courseScheduleVO);
    }

    @PostMapping("/free-schedule")
    @ApiOperation("自由排课")
    @Override

    public JsonVO<String> freeSchedule(@Param("courseScheduleDto")CourseScheduleDTO courseScheduleVO) {

        log.info("参数：{}",courseScheduleVO);
        return lessonSchduleService.freeSchedule(courseScheduleVO);
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
    public JsonVO<String> switchSchedule(CourseAppointStatusDTO courseAppointStatusDto) {
        return  lessonSchduleService.switchSchedule(courseAppointStatusDto);
    }
    @GetMapping("/student-status/list")
    @ApiOperation("分页查询学员上课状态列表")
    @Override
    public JsonVO<PageDTO<Map<String, Object>>> queryStudentsStatusList(StudentStatusQuery studentStatusQuery) {
        return JsonVO.success(lessonStudentService.queryStatusList(studentStatusQuery));
    }


    @PostMapping("batch-set-status")
    @ApiOperation("设置学员上课状态")
    @Override
    public JsonVO<Integer> batchSetStatus(@RequestBody SetStudentsStatusDTO setStudentsStatusDTO) {
        return JsonVO.success(lessonStudentService.batchSetStatus(
                setStudentsStatusDTO.getLessonStudentIds(),
                setStudentsStatusDTO.getStatus()));
    }

    @PostMapping("batch-restore")
    @ApiOperation("批量还原课程进度")
    @Override
    public JsonVO<Integer> batchRestore(@RequestBody RollBackDTO rollBackDTO) {
        return JsonVO.success(lessonStudentService.rollbackCourseNum(
                rollBackDTO.getLessonStudentIds()));
    }


    @PutMapping({"resume", "pause-resume"})
    @ApiOperation("停/复课")
    @Override
    public JsonVO<Integer> resumeLesson(@RequestBody CoursePauseResumeDTO coursePauseResumeDTO) {
        return JsonVO.success(lessonStudentService.pauseOrResumeLesson(
                coursePauseResumeDTO.getLessonIds(),
                coursePauseResumeDTO.getIsResume()));
    }

    @Override
    @ApiOperation("添加随课生")
    @PostMapping("/course-student")
    public JsonVO<Long> saveCourseStudent(@Valid @RequestBody CourseStudentDTO courseStudentDTO) {
        log.info("学生id:{}",courseStudentDTO.getStudentIds());
        Long resultId = casualStudentService.addCourseStudent(courseStudentDTO);
        return JsonVO.success(resultId);
    }

    @Override
    @GetMapping("/evaluation/list")
    @ApiOperation("获取课后点评列表（条件+分页）")
    public JsonVO<PageDTO<EvaluationVO>> queryPage(@Valid EvaluationQuery condition) {
        log.info("获取课后点评列表:{}",condition);
        PageDTO<EvaluationVO> pageResult = evaluationService.queryPage(condition);
        return JsonVO.success(pageResult);
    }

    @PostMapping("/evaluation")
    @Override
    @ApiOperation("保存点评")
    public JsonVO<Long> saveEvaluation(@Valid @RequestBody EvaluationDTO evaluationDTO) {
        Long count = evaluationService.saveEvaluation(evaluationDTO);
        return JsonVO.success(null);
    }


}
