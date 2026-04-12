package com.zeroone.star.j5.courseschedule.controller;

import com.zeroone.star.j5.courseschedule.service.ICasualStudentService;
import com.zeroone.star.j5.courseschedule.service.IEvaluationService;
import com.zeroone.star.project.dto.j5.courseschedule.*;
import com.zeroone.star.project.query.j5.courseschedule.*;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j5.courseschedule.CourseScheduleApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.courseschedule.CourseDetailVO;
import com.zeroone.star.project.vo.j5.courseschedule.CourseListVO;
import com.zeroone.star.project.vo.j5.courseschedule.EvaluationVO;
import com.zeroone.star.project.vo.j5.courseschedule.LessonCalendarVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("j5/courseschedule")
@Api(tags="课程表")
@Slf4j
public class CourseScheduleController implements CourseScheduleApis {

    @Resource
    IEvaluationService evaluationService;

    @Resource
    ICasualStudentService casualStudentService;



    @GetMapping("/calendar")
    @ApiOperation("获取课表日历（条件）")
    @Override
    public JsonVO<List<LessonCalendarVO>> queryCalendar(CourseQuery condition) {
        return null;
    }

    @GetMapping("/list")
    @ApiOperation("获取课次列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<CourseListVO>> queryCourseList(CourseListQuery courseListQuery) {
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
    public JsonVO<String> repeatSchedule(CourseScheduleDTO courseScheduleVO) {
        return null;
    }

    @PostMapping("/free-schedule")
    @ApiOperation("自由排课")
    @Override
    public JsonVO<String> freeSchedule(CourseScheduleDTO courseScheduleVO) {
        return null;
    }


    @PutMapping("/update-course")
    @ApiOperation("修改课次")
    @Override
    public JsonVO<String> updateCourse(UpdateCourseDTO updateCourseDTO) {
        return null;
    }

    @PutMapping("/batch-update-courses")
    @ApiOperation("批量修改课次")
    @Override
    public JsonVO<String> updateCourses(BatchUpdateCourseDTO batchUpdateCourseDTO) {
        return null;
    }

    @DeleteMapping("/delete-courses")
    @ApiOperation("删除课次")
    @Override
    public JsonVO<String> deleteCourses(List<Long> ids) {
        return null;
    }

    @PostMapping("/switch-schedule")
    @ApiOperation("预约课程开关")
    @Override
    public JsonVO<String> switchSchedule(CourseAppointStatusDTO courseAppointStatusDto) {
        return null;
    }

    @GetMapping("/student-status/list")
    @ApiOperation("分页查询学员上课状态列表")
    @Override
    public JsonVO<PageDTO<Map<String, Object>>> queryStudentsStatusList(StudentStatusQuery studentStatusQuery) {
        return JsonVO.success(null);
    }


    @PostMapping("batch-set-status")
    @ApiOperation("设置学员上课状态")
    @Override
    public JsonVO<Integer> batchSetStatus(SetStudentsStatusDTO setStudentsStatusDTO) {
        return JsonVO.success(0);
    }

    @PostMapping("batch-restore")
    @ApiOperation("批量还原课程进度")
    @Override
    public JsonVO<Integer> batchRestore(RollBackDTO rollBackDTO) {
        return JsonVO.success(0);
    }


    @PutMapping("resume")
    @ApiOperation("停/复课")
    @Override
    public JsonVO<Integer> resumeLesson(CoursePauseResumeDTO coursePauseResumeDTO) {
        return JsonVO.success(0);
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
