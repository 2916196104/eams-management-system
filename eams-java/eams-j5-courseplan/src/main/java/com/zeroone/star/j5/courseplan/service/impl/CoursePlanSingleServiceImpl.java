package com.zeroone.star.j5.courseplan.service.impl;

import cn.hutool.core.util.StrUtil;
import com.baomidou.mybatisplus.core.toolkit.Wrappers;
import com.zeroone.star.j5.courseplan.entity.Lesson;
import com.zeroone.star.j5.courseplan.entity.LessonSchedule;
import com.zeroone.star.j5.courseplan.entity.LessonScheduleSetting;
import com.zeroone.star.j5.courseplan.entity.LessonTeacher;
import com.zeroone.star.j5.courseplan.mapper.LessonMapper;
import com.zeroone.star.j5.courseplan.mapper.LessonScheduleMapper;
import com.zeroone.star.j5.courseplan.mapper.LessonScheduleSettingMapper;
import com.zeroone.star.j5.courseplan.mapper.LessonTeacherMapper;
import com.zeroone.star.j5.courseplan.service.ICoursePlanSingleService;
import com.zeroone.star.j5.courseplan.utils.ScheduleUtils;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

/**
 * 单个排课计划独立事务处理服务实现类
 * 支持事务隔离：每个排课计划独立生成，失败不影响其他计划
 */
@Slf4j
@Service
@RequiredArgsConstructor
public class CoursePlanSingleServiceImpl implements ICoursePlanSingleService {

    private final LessonScheduleMapper lessonScheduleMapper;
    private final LessonScheduleSettingMapper lessonScheduleSettingMapper;
    private final LessonMapper lessonMapper;
    private final LessonTeacherMapper lessonTeacherMapper;

    /**
     * 生成单个排课计划的课表
     * 使用独立事务，支持批量生成时的容错处理
     *
     * @param scheduleId   排课计划 ID
     * @param excludeHoliday 是否排除节假日
     * @param overwrite    是否覆盖已生成课表
     * @return 成功生成的课次数量
     */
    @Override
    @Transactional(rollbackFor = Exception.class)
    public int generateSingleSchedule(Long scheduleId, Boolean excludeHoliday, Boolean overwrite) {
        log.info("开始生成排课计划 [{}] 的课表，excludeHoliday: {}, overwrite: {}", scheduleId, excludeHoliday, overwrite);

        // 1. 查询排课计划
        LessonSchedule schedule = lessonScheduleMapper.selectById(scheduleId);
        if (schedule == null || schedule.getDeleted() != null && schedule.getDeleted() == 1) {
            throw new RuntimeException("排课计划不存在或已删除");
        }

        // 2. 检查是否已生成课表
        if (schedule.getState() != null && schedule.getState() == 1) {
            if (!Boolean.TRUE.equals(overwrite)) {
                log.info("排课计划 [{}] 已生成课表，跳过生成", scheduleId);
                return 0;
            }
            // 删除已生成的课表
            deleteLessonsByScheduleId(scheduleId);
        }

        // 3. 查询排课计划设置（上课时间安排）
        List<LessonScheduleSetting> settings = lessonScheduleSettingMapper.selectList(
                Wrappers.<LessonScheduleSetting>lambdaQuery()
                        .eq(LessonScheduleSetting::getScheduleId, scheduleId)
        );

        if (settings.isEmpty()) {
            throw new RuntimeException("排课计划 [{}] 没有设置上课时间");
        }

        // 4. 计算应上课总次数
        int totalTimes = 0;
        for (LessonScheduleSetting setting : settings) {
            int times = ScheduleUtils.calculateRuleOccurrences(
                    schedule.getStartDate(),
                    schedule.getEndDate(),
                    setting.getWeeks()
            );
            totalTimes += times;
        }
        log.info("排课计划 [{}] 计算应上课次数：{}", scheduleId, totalTimes);

        // 5. 生成课次
        int generatedCount = 0;
        LocalDate currentDate = schedule.getStartDate();
        int lessonSn = 1;

        while (!currentDate.isAfter(schedule.getEndDate())) {
            String weekStr = String.valueOf(currentDate.getDayOfWeek().getValue());

            for (LessonScheduleSetting setting : settings) {
                // 检查当前日期是否符合星期设置
                if (StrUtil.isNotBlank(setting.getWeeks()) &&
                        Arrays.asList(setting.getWeeks().split(",")).contains(weekStr)) {

                    // 检查是否需要排除节假日（这里可以扩展节假日判断逻辑）
                    if (Boolean.TRUE.equals(excludeHoliday) && isHoliday(currentDate)) {
                        continue;
                    }

                    // 创建课次
                    Lesson lesson = new Lesson();
                    lesson.setScheduleId(scheduleId);
                    lesson.setClassId(schedule.getClassId());
                    lesson.setCourseId(schedule.getCourseId());
                    lesson.setRoomId(setting.getRoomId());
                    lesson.setDate(currentDate);
                    lesson.setStartTime(setting.getStartTime());
                    lesson.setEndTime(setting.getEndTime());
                    lesson.setSn(lessonSn++);
                    lesson.setDecCount(schedule.getDecLessonCount());
                    lesson.setTeachType(1); // 默认授课方式
                    lesson.setState(1); // 进行中
                    lesson.setCreator(schedule.getCreator());
                    lesson.setOrgId(schedule.getOrgId());
                    lesson.setSchoolId(null); // 根据需要设置

                    lessonMapper.insert(lesson);
                    generatedCount++;

                    // 关联教师
                    if (StrUtil.isNotBlank(schedule.getTeacherIds())) {
                        List<Long> teacherIds = Arrays.stream(schedule.getTeacherIds().split(","))
                                .map(Long::valueOf)
                                .collect(Collectors.toList());

                        for (Long teacherId : teacherIds) {
                            LessonTeacher lessonTeacher = new LessonTeacher();
                            lessonTeacher.setLessonId(lesson.getId());
                            lessonTeacher.setTeacherId(teacherId);
                            lessonTeacher.setTypeNum(1); // 1-主讲老师
                            lessonTeacherMapper.insert(lessonTeacher);
                        }
                    }

                    // 关联助教
                    if (StrUtil.isNotBlank(schedule.getAssistantIds())) {
                        List<Long> assistantIds = Arrays.stream(schedule.getAssistantIds().split(","))
                                .map(Long::valueOf)
                                .collect(Collectors.toList());

                        for (Long assistantId : assistantIds) {
                            LessonTeacher lessonTeacher = new LessonTeacher();
                            lessonTeacher.setLessonId(lesson.getId());
                            lessonTeacher.setTeacherId(assistantId);
                            lessonTeacher.setTypeNum(2); // 2-助教
                            lessonTeacherMapper.insert(lessonTeacher);
                        }
                    }
                }
            }

            currentDate = currentDate.plusDays(1);
        }

        // 6. 更新排课计划状态
        LessonSchedule updateSchedule = new LessonSchedule();
        updateSchedule.setId(scheduleId);
        updateSchedule.setState(1); // 1-已生成
        lessonScheduleMapper.updateById(updateSchedule);

        log.info("排课计划 [{}] 生成课表完成，生成课次：{}", scheduleId, generatedCount);
        return generatedCount;
    }

    /**
     * 删除指定排课计划的所有课次
     */
    private void deleteLessonsByScheduleId(Long scheduleId) {
        List<Lesson> lessons = lessonMapper.selectList(
                Wrappers.<Lesson>lambdaQuery().eq(Lesson::getScheduleId, scheduleId)
        );

        if (!lessons.isEmpty()) {
            List<Long> lessonIds = lessons.stream().map(Lesson::getId).collect(Collectors.toList());

            // 删除关联的教师和学生
            lessonTeacherMapper.delete(Wrappers.<LessonTeacher>lambdaQuery()
                    .in(LessonTeacher::getLessonId, lessonIds));

            // 删除课次
            lessonMapper.deleteBatchIds(lessonIds);
        }

        log.info("删除排课计划 [{}] 的已生成课表", scheduleId);
    }

    /**
     * 判断是否为节假日
     * TODO: 需要实现具体的节假日判断逻辑（可以调用节假日 API 或查询数据库）
     */
    private boolean isHoliday(LocalDate date) {
        // 这里暂时返回 false，实际业务中需要根据具体需求实现
        // 例如：查询国家的法定节假日、周末等
        return false;
    }
}
