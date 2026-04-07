package com.zeroone.star.j5.courseschedule.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.extension.service.impl.*;
import com.zeroone.star.j5.courseschedule.entity.Lesson;
import com.zeroone.star.j5.courseschedule.entity.LessonStudent;
import com.zeroone.star.j5.courseschedule.mapper.LessonMapper;
import com.zeroone.star.j5.courseschedule.mapper.LessonStudentMapper;
import com.zeroone.star.j5.courseschedule.mapper.LessonTeacherMapper;
import com.zeroone.star.j5.courseschedule.service.CourseStudentService;
import com.zeroone.star.project.DO.j5.courseschedule.LessonTeacherDo;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.*;
import io.swagger.models.auth.In;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.util.ArrayList;
import java.util.List;

/**
 * <p>
 * 描述：课次学员关联服务实现类
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
@Service
public class CourseStudentServiceImpl extends ServiceImpl<LessonStudentMapper, LessonStudent> implements CourseStudentService {

    @Resource
    private LessonMapper lessonMapper;

    @Resource
    private LessonTeacherMapper lessonTeacherMapper;
    @Override
    public PageDTO<?> queryList(LessonParamDTO param) {
        // TODO skeleton only: add real query logic in next stage
        return null;
    }

    @Override
    public Integer batchSetStatus(List<Long> lessonStudentIds, String status) {
        // TODO skeleton only: add real batch status logic in next stage
        return 0;
    }

    @Override
    public Integer batchRollCall(List<LessonSignSaveDTO> signList) {
        // TODO skeleton only: add real batch roll-call logic in next stage
        return 0;
    }

    @Override
    public Integer changeLessonState(LessonChangeStateDTO dto) {
        // TODO skeleton only: add real lesson state transition logic in next stage
        return 0;
    }



    @Override
    public Integer rollbackCourseNum(List<Long> lessonStudentIds) {
        // TODO skeleton only: add real rollback logic in next stage
        return 0;
    }

    @Override
    public PageDTO<?> queryLessonCountLog(LessonCountLogQueryDTO queryDTO) {
        return null;
    }

    @Override
    @Transactional
    public Boolean updateCourse(UpdateCourseDTO dto) {
        Lesson lesson = lessonMapper.selectById(dto.getId());
        if (lesson == null) {
            throw new RuntimeException("课次不存在");
        }
        //  更新 lesson
        if (!isAllNull(dto)) {
            Lesson updateDo = new Lesson();
            BeanUtils.copyProperties(dto, updateDo);
            lessonMapper.updateById(updateDo);
        }
        // 更新老师关系
        if (dto.getTeacherIds() != null || dto.getAssistantIds() != null) {
            lessonTeacherMapper.delete(new LambdaQueryWrapper<LessonTeacherDo>()
                            .eq(LessonTeacherDo::getLessonId, dto.getId())
            );

            List<LessonTeacherDo> list = new ArrayList<>();

            if (dto.getTeacherIds() != null) {
                for (Long teacherId : dto.getTeacherIds()) {
                    LessonTeacherDo t = new LessonTeacherDo();
                    t.setLessonId(dto.getId());
                    t.setTeacherId(teacherId);
                    t.setTypeNum(1);
                    list.add(t);
                }
            }

            if (dto.getAssistantIds() != null) {
                for (Long assistantId : dto.getAssistantIds()) {
                    if (dto.getTeacherIds() != null && dto.getTeacherIds().contains(assistantId)) {
                        throw new RuntimeException("助教不能同时是授课老师，请检查人员选择：" + assistantId);
                    }
                    LessonTeacherDo t = new LessonTeacherDo();
                    t.setLessonId(dto.getId());
                    t.setTeacherId(assistantId);
                    t.setTypeNum(2);
                    list.add(t);
                }
            }

            if (!list.isEmpty()) {
                list.forEach(lessonTeacherMapper::insert);
            }
        }
        return true;
    }
    private boolean isAllNull(UpdateCourseDTO dto) {
        return dto.getTitle() == null &&
                dto.getSchoolId() == null &&
                dto.getCourseId() == null &&
                dto.getDate() == null &&
                dto.getStartTime() == null &&
                dto.getEndTime() == null &&
                dto.getRoomId() == null &&
                dto.getDecCount() == null &&
                dto.getBookable() == null;
    }
    @Override
    @Transactional
    public Boolean updateCourses(BatchUpdateCourseDTO dto) {

        List<Lesson> lessons = lessonMapper.selectBatchIds(dto.getUpdateIds());
        if (lessons == null || lessons.isEmpty()) {
            throw new RuntimeException("课次不存在");
        }
        // 获取 lesson 下的 status，判断是否为 1，有一个不是 1 就返回 0
        for (Lesson lesson : lessons) {
            if (lesson.getState() != 1) {
                log.error("课次状态异常，只能选中进行中的课程");
                return false;
            }
        }
        //更新部分数据
        LambdaUpdateWrapper<Lesson> updateWrapper = new LambdaUpdateWrapper<>();
        if (dto.getStartTime() != null) {
            updateWrapper.set(Lesson::getStartTime, dto.getStartTime());
        }
        if (dto.getEndTime() != null) {
            updateWrapper.set(Lesson::getEndTime, dto.getEndTime());
        }
        if (dto.getRoomId() != null) {
            updateWrapper.set(Lesson::getRoomId, dto.getRoomId());
        }
        // 特殊处理：DATE_ADD 函数（MP 支持直接拼 SQL 片段）
        if (dto.getChangeDays() != null) {
            updateWrapper.setSql("date = DATE_ADD(date, INTERVAL " + dto.getChangeDays() + " DAY)");
        }
        updateWrapper.in(Lesson::getId, dto.getUpdateIds());
        lessonMapper.update(null, updateWrapper);

        if (dto.getTeacherIds() != null || dto.getAssistantIds() != null) {
            LambdaQueryWrapper<LessonTeacherDo> deleteWrapper = new LambdaQueryWrapper<>();
            deleteWrapper.in(LessonTeacherDo::getLessonId, dto.getUpdateIds());
            lessonTeacherMapper.delete(deleteWrapper);

            List<LessonTeacherDo> list = new ArrayList<>();

            for (Long lessonId : dto.getUpdateIds()) {

                if (dto.getTeacherIds() != null) {
                    for (Long teacherId : dto.getTeacherIds()) {
                        LessonTeacherDo t = new LessonTeacherDo();
                        t.setLessonId(lessonId);
                        t.setTeacherId(teacherId);
                        t.setTypeNum(1);
                        list.add(t);
                    }
                }

                if (dto.getAssistantIds() != null) {
                    for (Long assistantId : dto.getAssistantIds()) {
                        if (dto.getTeacherIds() != null && dto.getTeacherIds().contains(assistantId)) {
                            throw new RuntimeException("助教不能同时是授课老师，请检查人员选择：" + assistantId);
                        }
                        LessonTeacherDo t = new LessonTeacherDo();
                        t.setLessonId(lessonId);
                        t.setTeacherId(assistantId);
                        t.setTypeNum(2);
                        list.add(t);
                    }
                }
            }

            if (!list.isEmpty()) {
                list.forEach(lessonTeacherMapper::insert);
            }

        }
        return true;
    }

    @Override
    public Boolean deleteCourses(List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            throw new RuntimeException("删除ID列表不能为空");
        }
        boolean success = lessonMapper.deleteBatchIds(ids) > 0;
        return success ;
    }

//    @Override
//    public PageDTO<?> queryLessonCountLog(LessonCountLogQueryDTO queryDTO) {
//        // TODO skeleton only: add real log query logic in next stage
//        return null;
//    }
}
