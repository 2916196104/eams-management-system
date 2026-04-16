package com.zeroone.star.stumanager.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j8.stumanager.common.LessonCountRecordQuery;
import com.zeroone.star.project.vo.j8.stumanager.common.LessonCountRecordVO;
import com.zeroone.star.stumanager.entity.Course;
import com.zeroone.star.stumanager.entity.Lesson;
import com.zeroone.star.stumanager.entity.Staff;
import com.zeroone.star.stumanager.entity.Student;
import com.zeroone.star.stumanager.entity.StudentLessonCountLog;
import com.zeroone.star.stumanager.mapper.StudentLessonCountLogMapper;
import com.zeroone.star.stumanager.service.ICourseService;
import com.zeroone.star.stumanager.service.ILessonService;
import com.zeroone.star.stumanager.service.IStaffService;
import com.zeroone.star.stumanager.service.IStudentLessonCountLogService;
import com.zeroone.star.stumanager.service.IStudentService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.Collections;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Set;
import java.util.function.Function;
import java.util.stream.Collectors;

@Service
public class StudentLessonCountLogServiceImpl extends ServiceImpl<StudentLessonCountLogMapper, StudentLessonCountLog> implements IStudentLessonCountLogService {

    @Resource
    private IStudentService studentService;

    @Resource
    private ICourseService courseService;

    @Resource
    private ILessonService lessonService;

    @Resource
    private IStaffService staffService;

    @Override
    public PageDTO<LessonCountRecordVO> queryLessonCountRecords(LessonCountRecordQuery query) {
        validateTimeRange(query.getBeginTime(), query.getEndTime());

        Page<StudentLessonCountLog> page = new Page<>(query.getPageIndex(), query.getPageSize());
        LambdaQueryWrapper<StudentLessonCountLog> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(StudentLessonCountLog::getStudentId, query.getStudentId());
        wrapper.eq(Objects.nonNull(query.getCourseId()), StudentLessonCountLog::getCourseId, query.getCourseId());
        wrapper.ge(Objects.nonNull(query.getBeginTime()), StudentLessonCountLog::getAddTime, query.getBeginTime());
        wrapper.le(Objects.nonNull(query.getEndTime()), StudentLessonCountLog::getAddTime, query.getEndTime());
        wrapper.orderByDesc(StudentLessonCountLog::getAddTime, StudentLessonCountLog::getId);

        Page<StudentLessonCountLog> result = page(page, wrapper);
        return buildPageDTO(result, buildRows(result.getRecords()));
    }

    private List<LessonCountRecordVO> buildRows(List<StudentLessonCountLog> records) {
        if (Objects.isNull(records) || records.isEmpty()) {
            return Collections.emptyList();
        }

        Map<Long, Student> studentMap = toStudentMap(collectIds(records, StudentLessonCountLog::getStudentId));
        Map<Long, Course> courseMap = toCourseMap(collectIds(records, StudentLessonCountLog::getCourseId));
        Map<Long, Lesson> lessonMap = toLessonMap(collectIds(records, StudentLessonCountLog::getLessonId));
        Map<Long, Staff> staffMap = toStaffMap(collectIds(records, StudentLessonCountLog::getStaffId));

        return records.stream().map(record -> {
            LessonCountRecordVO vo = new LessonCountRecordVO();
            vo.setId(record.getId());
            vo.setStudentId(record.getStudentId());
            vo.setCourseId(record.getCourseId());
            vo.setLessonId(record.getLessonId());
            vo.setChangeCount(record.getChangeCount());
            vo.setRemainingCount(record.getRemainingCount());
            vo.setStaffId(record.getStaffId());
            vo.setStage(record.getStage());
            vo.setAddTime(record.getAddTime());
            vo.setRemark(record.getRemark());

            Student student = studentMap.get(record.getStudentId());
            if (Objects.nonNull(student)) {
                vo.setStudentName(student.getName());
            }

            Course course = courseMap.get(record.getCourseId());
            if (Objects.nonNull(course)) {
                vo.setCourseName(course.getName());
            }

            Lesson lesson = lessonMap.get(record.getLessonId());
            if (Objects.nonNull(lesson)) {
                vo.setLessonTitle(lesson.getTitle());
            }

            Staff staff = staffMap.get(record.getStaffId());
            if (Objects.nonNull(staff)) {
                vo.setStaffName(staff.getName());
            }
            return vo;
        }).collect(Collectors.toList());
    }

    private Map<Long, Student> toStudentMap(Set<Long> ids) {
        if (ids.isEmpty()) {
            return Collections.emptyMap();
        }
        return studentService.listByIds(ids).stream()
                .filter(Objects::nonNull)
                .collect(Collectors.toMap(Student::getId, Function.identity(), (left, right) -> left));
    }

    private Map<Long, Course> toCourseMap(Set<Long> ids) {
        if (ids.isEmpty()) {
            return Collections.emptyMap();
        }
        return courseService.listByIds(ids).stream()
                .filter(Objects::nonNull)
                .collect(Collectors.toMap(Course::getId, Function.identity(), (left, right) -> left));
    }

    private Map<Long, Lesson> toLessonMap(Set<Long> ids) {
        if (ids.isEmpty()) {
            return Collections.emptyMap();
        }
        return lessonService.listByIds(ids).stream()
                .filter(Objects::nonNull)
                .collect(Collectors.toMap(Lesson::getId, Function.identity(), (left, right) -> left));
    }

    private Map<Long, Staff> toStaffMap(Set<Long> ids) {
        if (ids.isEmpty()) {
            return Collections.emptyMap();
        }
        return staffService.listByIds(ids).stream()
                .filter(Objects::nonNull)
                .collect(Collectors.toMap(Staff::getId, Function.identity(), (left, right) -> left));
    }

    private <T> Set<Long> collectIds(List<T> list, Function<T, Long> getter) {
        return list.stream()
                .map(getter)
                .filter(Objects::nonNull)
                .collect(Collectors.toCollection(LinkedHashSet::new));
    }

    private <T> PageDTO<T> buildPageDTO(Page<?> page, List<T> rows) {
        PageDTO<T> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex(page.getCurrent());
        pageDTO.setPageSize(page.getSize());
        pageDTO.setTotal(page.getTotal());
        pageDTO.setPages(page.getPages());
        pageDTO.setRows(rows);
        return pageDTO;
    }

    private void validateTimeRange(LocalDateTime beginTime, LocalDateTime endTime) {
        if (Objects.nonNull(beginTime) && Objects.nonNull(endTime) && beginTime.isAfter(endTime)) {
            throw new IllegalArgumentException("beginTime cannot be after endTime");
        }
    }
}
