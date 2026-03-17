package com.zeroone.star.stumanager.controller.common;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j8.stumanager.common.LessonCountRecordsApis;
import com.zeroone.star.project.query.j8.stumanager.common.LessonCountRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.common.LessonCountRecordVO;
import com.zeroone.star.stumanager.entity.Course;
import com.zeroone.star.stumanager.entity.Lesson;
import com.zeroone.star.stumanager.entity.Staff;
import com.zeroone.star.stumanager.entity.Student;
import com.zeroone.star.stumanager.entity.StudentLessonCountLog;
import com.zeroone.star.stumanager.service.ICourseService;
import com.zeroone.star.stumanager.service.ILessonService;
import com.zeroone.star.stumanager.service.IStaffService;
import com.zeroone.star.stumanager.service.IStudentLessonCountLogService;
import com.zeroone.star.stumanager.service.IStudentService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;
import java.util.Objects;

/**
 * 消课记录
 */
@RestController
@Validated
@RequestMapping("/common/lesson-count-records")
@Api(tags = "共用接口-消课记录")
public class LessonCountRecordsController implements LessonCountRecordsApis {
    @Resource
    private IStudentLessonCountLogService studentLessonCountLogService;

    @Resource
    private IStudentService studentService;

    @Resource
    private ICourseService courseService;

    @Resource
    private ILessonService lessonService;

    @Resource
    private IStaffService staffService;

    @ApiOperation("获取消课记录")
    @GetMapping("/query-lesson-count-records")
    @Override
    public JsonVO<PageDTO<LessonCountRecordVO>> queryLessonCountRecords(@Validated LessonCountRecordQuery query) {
        Page<StudentLessonCountLog> page = new Page<>(query.getPageIndex(), query.getPageSize());
        LambdaQueryWrapper<StudentLessonCountLog> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(StudentLessonCountLog::getStudentId, query.getStudentId());
        wrapper.eq(Objects.nonNull(query.getCourseId()), StudentLessonCountLog::getCourseId, query.getCourseId());
        wrapper.ge(Objects.nonNull(query.getBeginTime()), StudentLessonCountLog::getAddTime, query.getBeginTime());
        wrapper.le(Objects.nonNull(query.getEndTime()), StudentLessonCountLog::getAddTime, query.getEndTime());
        wrapper.orderByDesc(StudentLessonCountLog::getAddTime, StudentLessonCountLog::getId);
        Page<StudentLessonCountLog> result = studentLessonCountLogService.page(page, wrapper);
        return JsonVO.success(PageDTO.create(result, this::toLessonCountRecordVO));
    }

    private LessonCountRecordVO toLessonCountRecordVO(StudentLessonCountLog log) {
        LessonCountRecordVO vo = new LessonCountRecordVO();
        vo.setId(log.getId());
        vo.setStudentId(log.getStudentId());
        vo.setCourseId(log.getCourseId());
        vo.setLessonId(log.getLessonId());
        vo.setChangeCount(log.getChangeCount());
        vo.setRemainingCount(log.getRemainingCount());
        vo.setStaffId(log.getStaffId());
        vo.setStage(log.getStage());
        vo.setAddTime(log.getAddTime());
        vo.setRemark(log.getRemark());

        Student student = studentService.getById(log.getStudentId());
        if (Objects.nonNull(student)) {
            vo.setStudentName(student.getName());
        }

        if (Objects.nonNull(log.getCourseId())) {
            Course course = courseService.getById(log.getCourseId());
            if (Objects.nonNull(course)) {
                vo.setCourseName(course.getName());
            }
        }

        if (Objects.nonNull(log.getLessonId())) {
            Lesson lesson = lessonService.getById(log.getLessonId());
            if (Objects.nonNull(lesson)) {
                vo.setLessonTitle(lesson.getTitle());
            }
        }

        if (Objects.nonNull(log.getStaffId())) {
            Staff staff = staffService.getById(log.getStaffId());
            if (Objects.nonNull(staff)) {
                vo.setStaffName(staff.getName());
            }
        }

        return vo;
    }
}
