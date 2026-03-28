package com.zeroone.star.j5.courseplan.service.impl;

import cn.hutool.core.collection.CollUtil;
import cn.hutool.core.util.StrUtil;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.toolkit.Wrappers;
import com.zeroone.star.j5.courseplan.entity.*;
import com.zeroone.star.j5.courseplan.mapper.*;
import com.zeroone.star.j5.courseplan.service.ICoursePlanService;
import com.zeroone.star.j5.courseplan.service.ICoursePlanSingleService;
import com.zeroone.star.project.dto.j5.courseplan.BatchGenerateLessonDTO;
import com.zeroone.star.project.dto.j5.courseplan.ConflictCheckDTO;
import com.zeroone.star.project.dto.j5.courseplan.DeleteLessonDTO;
import com.zeroone.star.project.vo.j5.courseschedule.BatchGenerateLessonVO;
import com.zeroone.star.project.vo.j5.courseschedule.ConflictCheckVO;
import com.zeroone.star.project.vo.j5.courseschedule.ConflictDetailVO;
import com.zeroone.star.project.vo.j5.courseschedule.DeleteLessonResultVO;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collectors;

@Slf4j
@Service
@RequiredArgsConstructor
public class CoursePlanServiceImpl implements ICoursePlanService {

    private final ICoursePlanSingleService coursePlanSingleService;

    private final LessonScheduleMapper lessonScheduleMapper;
    private final LessonScheduleSettingMapper lessonScheduleSettingMapper;
    private final LessonMapper lessonMapper;
    private final LessonTeacherMapper lessonTeacherMapper;
    private final LessonStudentMapper lessonStudentMapper;

    @Override
    public BatchGenerateLessonVO batchGenerateLessons(BatchGenerateLessonDTO dto) {
        log.info("执行批量生成课表 DTO: {}", dto);
        List<Long> targetScheduleIds = dto.getScheduleIds();

        if (CollUtil.isEmpty(targetScheduleIds)) {
            targetScheduleIds = lessonScheduleMapper.selectList(
                    Wrappers.<LessonSchedule>lambdaQuery().eq(LessonSchedule::getState, 0)
            ).stream().map(LessonSchedule::getId).collect(Collectors.toList());
        }

        int successCount = 0;
        int totalLessonCount = 0;
        List<Long> failedList = new ArrayList<>();

        for (Long scheduleId : targetScheduleIds) {
            try {
                // 事务隔离：生成单个排课计划
                int count = coursePlanSingleService.generateSingleSchedule(scheduleId, dto.getExcludeHoliday(), dto.getOverwrite());
                successCount++;
                totalLessonCount += count;
            } catch (Exception e) {
                log.error("排课计划 [{}] 生成课表失败", scheduleId, e);
                failedList.add(scheduleId);
            }
        }

        BatchGenerateLessonVO vo = new BatchGenerateLessonVO();
        vo.setTotalCount(targetScheduleIds.size());
        vo.setSuccessCount(successCount);
        vo.setLessonCount(totalLessonCount);
        vo.setFailedList(failedList);
        return vo;
    }

    @Override
    public ConflictCheckVO checkConflict(ConflictCheckDTO dto) {
        log.info("执行冲突检查 DTO: {}", dto);
        List<ConflictDetailVO> conflicts = new ArrayList<>();
        List<LessonSchedule> schedulesToCheck = new ArrayList<>();

        if (CollUtil.isNotEmpty(dto.getScheduleIds())) {
            schedulesToCheck = lessonScheduleMapper.selectBatchIds(dto.getScheduleIds());
        }

        for (LessonSchedule planDO : schedulesToCheck) {
            if (Boolean.TRUE.equals(dto.getIgnoreGenerated()) && planDO.getState() != null && planDO.getState() == 1) {
                continue;
            }

            List<LessonScheduleSetting> settingDOs = lessonScheduleSettingMapper.selectList(
                    Wrappers.<LessonScheduleSetting>lambdaQuery().eq(LessonScheduleSetting::getScheduleId, planDO.getId())
            );

            Set<Long> teacherIdsToCheck = new HashSet<>();
            if (StrUtil.isNotBlank(planDO.getTeacherIds())) {
                Arrays.stream(planDO.getTeacherIds().split(",")).map(Long::valueOf).forEach(teacherIdsToCheck::add);
            }
            if (StrUtil.isNotBlank(planDO.getAssistantIds())) {
                Arrays.stream(planDO.getAssistantIds().split(",")).map(Long::valueOf).forEach(teacherIdsToCheck::add);
            }

            LocalDate curr = planDO.getStartDate();
            while (!curr.isAfter(planDO.getEndDate())) {
                String weekStr = String.valueOf(curr.getDayOfWeek().getValue());

                for (LessonScheduleSetting settingDO : settingDOs) {
                    if (StrUtil.isNotBlank(settingDO.getWeeks()) && Arrays.asList(settingDO.getWeeks().split(",")).contains(weekStr)) {

                        LambdaQueryWrapper<Lesson> overlapQuery = Wrappers.lambdaQuery();
                        overlapQuery.eq(Lesson::getDate, curr)
                                .lt(Lesson::getStartTime, settingDO.getEndTime())
                                .gt(Lesson::getEndTime, settingDO.getStartTime())
                                .ne(Lesson::getScheduleId, planDO.getId());

                        List<Lesson> overlapLessonDOs = lessonMapper.selectList(overlapQuery);

                        for (Lesson existingLessonDO : overlapLessonDOs) {
                            String timeDesc = curr + " " + settingDO.getStartTime() + "-" + settingDO.getEndTime();

                            // 手动组装：教室占用冲突
                            if (("all".equals(dto.getCheckType()) || "room".equals(dto.getCheckType()))
                                    && settingDO.getRoomId() != null
                                    && settingDO.getRoomId().equals(existingLessonDO.getRoomId())) {

                                ConflictDetailVO detail = new ConflictDetailVO();
                                detail.setScheduleId(planDO.getId());
                                detail.setConflictType("ROOM_OCCUPIED");
                                detail.setConflictWith(existingLessonDO.getId());
                                detail.setConflictTime(timeDesc);
                                conflicts.add(detail);
                            }

                            // 手动组装：教师时间冲突
                            if (("all".equals(dto.getCheckType()) || "teacher".equals(dto.getCheckType()))
                                    && !teacherIdsToCheck.isEmpty()) {

                                List<Long> existingTeacherIds = lessonTeacherMapper.selectList(
                                        Wrappers.<LessonTeacher>lambdaQuery().eq(LessonTeacher::getLessonId, existingLessonDO.getId())
                                ).stream().map(LessonTeacher::getTeacherId).collect(Collectors.toList());

                                if (!Collections.disjoint(teacherIdsToCheck, existingTeacherIds)) {
                                    ConflictDetailVO detail = new ConflictDetailVO();
                                    detail.setScheduleId(planDO.getId());
                                    detail.setConflictType("TEACHER_TIME");
                                    detail.setConflictWith(existingLessonDO.getId());
                                    detail.setConflictTime(timeDesc);
                                    conflicts.add(detail);
                                }
                            }
                        }
                    }
                }
                curr = curr.plusDays(1);
            }

            if (!conflicts.isEmpty()) {
                LessonSchedule updateConflict = new LessonSchedule();
                updateConflict.setId(planDO.getId());
                updateConflict.setConflictIds(conflicts.stream().map(c -> String.valueOf(c.getConflictWith())).collect(Collectors.joining(",")));
                lessonScheduleMapper.updateById(updateConflict);
            }
        }

        ConflictCheckVO vo = new ConflictCheckVO();
        vo.setHasConflict(!conflicts.isEmpty());
        vo.setConflictCount(conflicts.size());
        vo.setConflicts(conflicts);
        return vo;
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public DeleteLessonResultVO deleteLessons(DeleteLessonDTO dto) {
        log.info("执行删除已生成课表 DTO: {}", dto);
        int successCount = 0;
        int deletedLessonCount = 0;
        List<Long> failedList = new ArrayList<>();

        for (Long scheduleId : dto.getScheduleIds()) {
            try {
                List<Lesson> lessonDOs = lessonMapper.selectList(
                        Wrappers.<Lesson>lambdaQuery().eq(Lesson::getScheduleId, scheduleId)
                );

                if (CollUtil.isNotEmpty(lessonDOs)) {
                    List<Long> lessonIdsToDelete = new ArrayList<>();

                    for (Lesson lessonDO : lessonDOs) {
                        if (Boolean.FALSE.equals(dto.getForceDelete())) {
                            Long signedCount = lessonStudentMapper.selectCount(
                                    Wrappers.<LessonStudent>lambdaQuery()
                                            .eq(LessonStudent::getLessonId, lessonDO.getId())
                                            .gt(LessonStudent::getSignState, 0)
                            );
                            if (signedCount > 0) continue;
                        }
                        lessonIdsToDelete.add(lessonDO.getId());
                    }

                    if (CollUtil.isNotEmpty(lessonIdsToDelete)) {
                        lessonStudentMapper.delete(Wrappers.<LessonStudent>lambdaQuery().in(LessonStudent::getLessonId, lessonIdsToDelete));
                        lessonTeacherMapper.delete(Wrappers.<LessonTeacher>lambdaQuery().in(LessonTeacher::getLessonId, lessonIdsToDelete));
                        lessonMapper.deleteBatchIds(lessonIdsToDelete);

                        deletedLessonCount += lessonIdsToDelete.size();
                    }
                }

                LessonSchedule scheduleDO = new LessonSchedule();
                scheduleDO.setId(scheduleId);
                scheduleDO.setState(0);
                scheduleDO.setConflictIds("");
                lessonScheduleMapper.updateById(scheduleDO);

                successCount++;
            } catch (Exception e) {
                log.error("删除排课计划 [{}] 失败: {}", scheduleId, e.getMessage());
                failedList.add(scheduleId);
                throw new RuntimeException("删除触发回滚", e);
            }
        }

        DeleteLessonResultVO vo = new DeleteLessonResultVO();
        vo.setTotalCount(dto.getScheduleIds().size());
        vo.setSuccessCount(successCount);
        vo.setLessonCount(deletedLessonCount);
        vo.setFailedList(failedList);
        return vo;
    }
}