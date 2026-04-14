package com.zeroone.star.j5.courseschedule.service.impl;

import cn.hutool.db.PageResult;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j5.courseschedule.entity.*;
import com.zeroone.star.j5.courseschedule.mapper.*;
import com.zeroone.star.j5.courseschedule.service.ILessonService;
import com.zeroone.star.project.DO.j5.courseschedule.StaffDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonQueryDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonSaveDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonUpdateDTO;
import com.zeroone.star.project.vo.j5.courseschedule.LessonCalendarVO;
import com.zeroone.star.project.vo.j5.courseschedule.LessonDetailVO;
import com.zeroone.star.project.vo.j5.courseschedule.LessonListVO;
import lombok.RequiredArgsConstructor;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;

import java.lang.Class;
import java.time.LocalDateTime;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

@Service
@RequiredArgsConstructor
public class LessonServiceImpl extends ServiceImpl<LessonMapper, Lesson> implements ILessonService {

    private final CourseMapper courseMapper;
    private final EduClassMapper educlassMapper;
    private final StaffMapper staffMapper;
    private final ClassroomMapper classroomMapper;
    private final LessonStudentMapper lessonStudentMapper;

    @Override
    public List<LessonCalendarVO> calendar(LessonQueryDTO query) {
        LambdaQueryWrapper<Lesson> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(Lesson::getDeleted, 0);
        wrapper.ge(query.getStartDate() != null, Lesson::getDate, query.getStartDate());
        wrapper.le(query.getEndDate() != null, Lesson::getDate, query.getEndDate());
        wrapper.eq(query.getClassId() != null, Lesson::getClassId, query.getClassId());
        wrapper.eq(query.getCourseId() != null, Lesson::getCourseId, query.getCourseId());
        wrapper.eq(query.getTeacherId() != null, Lesson::getTeacherId, query.getTeacherId());
        wrapper.eq(query.getRoomId() != null, Lesson::getRoomId, query.getRoomId());

        List<Lesson> list = list(wrapper);

        // 安全转 Map，防空指针、防重复Key
        Map<Long, String> courseMap = courseMapper.selectList(null).stream()
                .filter(c -> c.getId() != null && c.getName() != null)
                .collect(Collectors.toMap(Course::getId, Course::getName, (a, b) -> a));

        Map<Long, String> classMap = educlassMapper.selectList(null).stream()
                .filter(c -> c.getId() != null && c.getName() != null)
                .collect(Collectors.toMap(EduClass::getId, EduClass::getName, (a, b) -> a));

        Map<Long, String> teacherMap = staffMapper.selectList(null).stream()
                .filter(s -> s.getId() != null && s.getName() != null)
                .collect(Collectors.toMap(StaffDO::getId, StaffDO::getName, (a, b) -> a));

        Map<Long, String> roomMap = classroomMapper.selectList(null).stream()
                .filter(c -> c.getId() != null && c.getName() != null)
                .collect(Collectors.toMap(Classroom::getId, Classroom::getName, (a, b) -> a));

        // 修复 toList()
        return list.stream().map(l -> {
            LessonCalendarVO vo = new LessonCalendarVO();
            vo.setId(l.getId());
            vo.setTitle(l.getTitle());
            vo.setDate(l.getDate());
            vo.setStartTime(l.getStartTime());
            vo.setEndTime(l.getEndTime());
            vo.setClassName(classMap.get(l.getClassId()));
            vo.setCourseName(courseMap.get(l.getCourseId()));
            vo.setTeacherName(teacherMap.get(l.getTeacherId()));
            vo.setClassroomName(roomMap.get(l.getRoomId()));

            return vo;
        }).collect(Collectors.toList());
    }

    // ====================== 🔥 适配你的 PageDTO + 分页修复 ======================
    @Override
    public PageDTO<LessonListVO> pageList(LessonQueryDTO query) {
        LambdaQueryWrapper<Lesson> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(Lesson::getDeleted, 0);
        wrapper.ge(query.getStartDate() != null, Lesson::getDate, query.getStartDate());
        wrapper.le(query.getEndDate() != null, Lesson::getDate, query.getEndDate());
        wrapper.eq(query.getClassId() != null, Lesson::getClassId, query.getClassId());
        wrapper.eq(query.getCourseId() != null, Lesson::getCourseId, query.getCourseId());
        wrapper.eq(query.getTeacherId() != null, Lesson::getTeacherId, query.getTeacherId());
        wrapper.eq(query.getState() != null, Lesson::getState, query.getState());

        Page<Lesson> page = page(
                new Page<>(query.getPageIndex(), query.getPageSize()),
                wrapper
        );

        return PageDTO.create(page, lesson -> {
            LessonListVO vo = new LessonListVO();
            vo.setId(lesson.getId());
            vo.setTitle(lesson.getTitle());
            vo.setSn(lesson.getSn());
            vo.setDate(lesson.getDate());
            vo.setStartTime(lesson.getStartTime());
            vo.setEndTime(lesson.getEndTime());
            vo.setState(lesson.getState());
            vo.setShouldCount(lesson.getDecCount());

            EduClass c = educlassMapper.selectById(lesson.getClassId());
            Course co = courseMapper.selectById(lesson.getCourseId());
            StaffDO s = staffMapper.selectById(lesson.getTeacherId());

            vo.setClassName(c == null ? "" : c.getName());
            vo.setCourseName(co == null ? "" : co.getName());
            vo.setTeacherName(s == null ? "" : s.getName());

            LambdaQueryWrapper<LessonStudent> q = new LambdaQueryWrapper<>();
            q.eq(LessonStudent::getLessonId, lesson.getId()).eq(LessonStudent::getSignState, 1);
            vo.setRealCount(lessonStudentMapper.selectCount(q).intValue());
            return vo;
        });
    }

    @Override
    public LessonDetailVO detail(Long id) {
        Lesson l = getById(id);
        if (l == null) return null;

        EduClass clazz = educlassMapper.selectById(l.getClassId());
        Course course = courseMapper.selectById(l.getCourseId());
        StaffDO staff = staffMapper.selectById(l.getTeacherId());
        Classroom classroom = classroomMapper.selectById(l.getRoomId());

        LessonDetailVO vo = new LessonDetailVO();
        vo.setId(l.getId());
        vo.setTitle(l.getTitle());
        vo.setSn(l.getSn());
        vo.setDate(l.getDate());
        vo.setStartTime(l.getStartTime());
        vo.setEndTime(l.getEndTime());
        vo.setClassName(clazz == null ? "" : clazz.getName());
        vo.setCourseName(course == null ? "" : course.getName());
        vo.setTeacherName(staff == null ? "" : staff.getName());
        vo.setRoomName(classroom == null ? "" : classroom.getName());
        vo.setState(l.getState());
        vo.setShouldCount(l.getDecCount());
        vo.setRemark(l.getRemark());

        LambdaQueryWrapper<LessonStudent> q = new LambdaQueryWrapper<>();
        q.eq(LessonStudent::getLessonId, l.getId()).eq(LessonStudent::getSignState, 1);
        vo.setRealCount(lessonStudentMapper.selectCount(q).intValue());
        return vo;
    }

    @Override
    public boolean saveLesson(LessonSaveDTO dto) {
        Lesson lesson = new Lesson();
        BeanUtils.copyProperties(dto, lesson);
        lesson.setAddTime(LocalDateTime.now());
        lesson.setEditTime(LocalDateTime.now());
        lesson.setDeleted(false);
        return save(lesson);
    }

    @Override
    public boolean updateLesson(LessonUpdateDTO dto) {
        Lesson lesson = new Lesson();
        BeanUtils.copyProperties(dto, lesson);
        lesson.setEditTime(LocalDateTime.now());
        return updateById(lesson);
    }
}
