package com.zeroone.star.j5.courseschedule.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j5.courseschedule.entity.Lesson;
import com.zeroone.star.j5.courseschedule.mapper.*;
import com.zeroone.star.j5.courseschedule.service.ICasualStudentService;
import com.zeroone.star.project.DO.j5.classmanager.StudentDO;
import com.zeroone.star.project.DO.j5.courseschedule.CourseStudentDO;
import com.zeroone.star.project.DO.j5.courseschedule.LessonDo;
import com.zeroone.star.project.DO.j5.courseschedule.StaffDO;
import com.zeroone.star.project.dto.j5.courseschedule.CourseStudentDTO;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;
import org.springframework.util.CollectionUtils;
import org.springframework.util.StringUtils;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

/**
 * @author silvan
 * @description
 */
@Service
@Slf4j
public class ICasualStudentServiceImpl extends ServiceImpl<CasualStudentMapper, CourseStudentDO>implements ICasualStudentService {

    @Resource
    private CourseStudentMapper courseStudentMapper;

    @Resource
    private StudentMapper studentMapper;

    @Resource
    private LessonDoMapper lessonDoMapper;

    @Resource
    private StaffMapper staffMapper;

    public ICasualStudentServiceImpl(CourseStudentMapper courseStudentMapper) {
        this.courseStudentMapper = courseStudentMapper;
    }

    /*
    * 添加随课生
    * */
    @Override

    public Long addCourseStudent(CourseStudentDTO courseStudentDTO) {
        // 获取学生ID列表
        List<Long> studentIds = courseStudentDTO.getStudentIds();
        // 批量构建DO
        List<CourseStudentDO> students = new ArrayList<>();

        for (Long studentId : studentIds) {
            // ====================== 1. 判断该学生在当前课次是否已存在（正确业务）======================
            LambdaQueryWrapper<CourseStudentDO> queryWrapper = new LambdaQueryWrapper<>();
            queryWrapper.eq(CourseStudentDO::getStudentId, studentId);
            queryWrapper.eq(CourseStudentDO::getLessonId, courseStudentDTO.getLessonId());
            CourseStudentDO exist = courseStudentMapper.selectOne(queryWrapper);

            // 存在则抛出异常
            if (exist != null) {
                throw new RuntimeException("该学生已在当前课次存在，不可重复添加");
            }

            // 先查询学生
            StudentDO student = studentMapper.selectById(studentId);
            if (student == null) {
                throw new RuntimeException("学生ID【" + studentId + "】不存在，请检查数据");
            }

            // 查询课次 & 教师信息
            LessonDo lesson = lessonDoMapper.selectById(courseStudentDTO.getLessonId());
            if (lesson == null) {
                throw new RuntimeException("课次不存在");
            }

            StaffDO staff = staffMapper.selectById(lesson.getTeacherId());

            log.info("老师id：{}",staff.getId());

            // ====================== 4. 创建随课生DO ======================
            CourseStudentDO courseStudentDO = new CourseStudentDO();
            BeanUtils.copyProperties(courseStudentDTO, courseStudentDO);

            // 基础字段
            courseStudentDO.setStudentId(studentId);
            courseStudentDO.setClassId(null); // 随课生
            courseStudentDO.setAddTime(LocalDateTime.now());

            // 置空默认字段
            courseStudentDO.setDecLessonCount(null);
            courseStudentDO.setLessonCount(null);
            courseStudentDO.setTeacherId(null);
            courseStudentDO.setSignTime(null);
            courseStudentDO.setSignType(null);
            courseStudentDO.setSignState(null);
            courseStudentDO.setScore(null);
            courseStudentDO.setEvaluation(null);

            // 业务字段
            courseStudentDO.setConsumeCourseId(courseStudentDTO.getLessonId());
            courseStudentDO.setConsumeStudentCourseId(null);
            courseStudentDO.setCounselor(student.getCounselor());
            courseStudentDO.setOrgId(staff.getOrgId());

            students.add(courseStudentDO);
        }

        // 批量保存
        boolean result = this.saveBatch(students);
        return result ? 1L : 0L;
    }
}
