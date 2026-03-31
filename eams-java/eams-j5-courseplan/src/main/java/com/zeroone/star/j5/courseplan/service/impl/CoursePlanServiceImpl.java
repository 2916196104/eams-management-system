package com.zeroone.star.j5.courseplan.service.impl;


import cn.hutool.core.bean.BeanUtil;
import cn.hutool.core.collection.CollUtil;
import cn.hutool.core.util.StrUtil;
import com.alibaba.nacos.client.naming.utils.CollectionUtils;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.toolkit.Wrappers;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j5.courseplan.entity.*;
import com.zeroone.star.j5.courseplan.mapper.*;
import com.zeroone.star.j5.courseplan.service.*;
import com.zeroone.star.j5.courseplan.utils.ScheduleUtils;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.j5.courseplan.BatchGenerateLessonDTO;
import com.zeroone.star.project.dto.j5.courseplan.ConflictCheckDTO;
import com.zeroone.star.project.dto.j5.courseplan.DeleteLessonDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonScheduleSettingDTO;
import com.zeroone.star.project.dto.j5.courseschedule.ScheduleSaveDTO;
import com.zeroone.star.project.query.j5.courseplan.SchedulePlanQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.courseplan.LessonScheduleVO;
import com.zeroone.star.project.vo.j5.courseplan.SchedulePlanVO;
import com.zeroone.star.project.vo.j5.courseschedule.BatchGenerateLessonVO;
import com.zeroone.star.project.vo.j5.courseschedule.ConflictCheckVO;
import com.zeroone.star.project.vo.j5.courseschedule.ConflictDetailVO;
import com.zeroone.star.project.vo.j5.courseschedule.DeleteLessonResultVO;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;

@Slf4j
@Service
@RequiredArgsConstructor
public class CoursePlanServiceImpl extends ServiceImpl<ScheduleMapper, LessonSchedule> implements CoursePlanService {
    @Autowired
    private UserHolder userHolder;
    @Autowired
    private ScheduleMapper scheduleMapper;
    @Autowired
    private CoursePlanService coursePlanService;
    @Autowired
    private LessonScheduleSettingService lessonScheduleSettingService;
    @Autowired
    private StaffService staffService;
    @Autowired
    private StaffOrgInfoService staffOrgInfoService;


    private final ICoursePlanSingleService coursePlanSingleService;

    private final LessonScheduleMapper lessonScheduleMapper;
    private final LessonScheduleSettingMapper lessonScheduleSettingMapper;
    private final LessonMapper lessonMapper;
    private final LessonTeacherMapper lessonTeacherMapper;
    private final LessonStudentMapper lessonStudentMapper;



    /*
    * 排课计划 获取计划列表（条件+分页）
    * */
    @Override
    public Page<SchedulePlanVO> listAll(SchedulePlanQuery query) {
        // 1、创建分页查询对象
        Page<SchedulePlanVO> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // 2、因为是多表联查，所以需要用xml获取数据
        return scheduleMapper.listAll(page, query);
    }


    /*
     * 保存或更新排课计划信息
     * */
    @Override
    @Transactional
    public JsonVO<Long> saveOrUpdateSchedule(ScheduleSaveDTO scheduleSaveDTO) {
        // 1、用于判断是更新还是插入
        Boolean isUpdate = scheduleSaveDTO.getId() != null;

        // 2. 类型转换 (主表)
        LessonSchedule lessonSchedule = BeanUtil.toBean(scheduleSaveDTO, LessonSchedule.class);

        // 获取排课计划的上课时间
        List<LessonScheduleSettingDTO> lessonScheduleSettingList = scheduleSaveDTO.getSettingList();

        // ================= 公共逻辑处理 (无论新增还是修改) =================

        // 3. 计算 times (排课次数)
        // 如果为 null，默认按日期排满
        if (scheduleSaveDTO.getTimes() == null) {
            int totalTimes = 0;
            // 遍历每一个子表设置项（每一行代表一个独立的时间段规则）
            for (LessonScheduleSettingDTO setting : lessonScheduleSettingList) {
                // 1. 计算当前这一行规则（比如：周一 08:00-09:00）在范围内有多少天
                int ruleCount = ScheduleUtils.calculateRuleOccurrences(
                        lessonSchedule.getStartDate(),
                        lessonSchedule.getEndDate(),
                        setting.getWeeks()
                );
                // 累加到总数
                totalTimes += ruleCount;
            }
            // 回填总数
            lessonSchedule.setTimes(totalTimes);
        }

        // 4. 获取当前登录用户id
        Long currentUserId = 2001L;
//        try {
//            // 获取当前登录用户的id
//            String id = userHolder.getCurrentUser().getId();
//            currentUserId = Long.valueOf(id);
//        } catch (Exception e) {
//            throw new RuntimeException(e);
//        }

        // 设置编辑者、编辑时间
        lessonSchedule.setEditor(currentUserId);
        lessonSchedule.setEditTime(LocalDateTime.now());

        // ================= 分支处理：更新 vs 新增 =================

        // 更新
        if (isUpdate){
            // 5、删除lesson_schedule_setting表数据
            LambdaQueryWrapper<LessonScheduleSetting> settingLambdaQueryWrapper = new LambdaQueryWrapper<>();
            settingLambdaQueryWrapper.eq(LessonScheduleSetting::getScheduleId, lessonSchedule.getId());
            lessonScheduleSettingService.remove(settingLambdaQueryWrapper);

            // 6、进行更新操作
            this.updateById(lessonSchedule);

        }
        // 新增
        else{
            // 7. 设置新增特有字段
            lessonSchedule.setState(0); // 默认未生成
            lessonSchedule.setCreator(currentUserId); // 创建人
            lessonSchedule.setAddTime(LocalDateTime.now()); // 创建时间
            lessonSchedule.setDeleted(0); // 未删除
            lessonSchedule.setConflictIds(null); // 初始为未检查

            // 8. 填充组织信息 (根据创建人)
            Staff staff = staffService.getById(currentUserId);
            LambdaQueryWrapper<StaffOrgInfo> staffOrgInfoLambdaQueryWrapper = new LambdaQueryWrapper<>();
            staffOrgInfoLambdaQueryWrapper.eq(StaffOrgInfo::getStaffId, staff.getId());
            StaffOrgInfo one = staffOrgInfoService.getOne(staffOrgInfoLambdaQueryWrapper);
            // 设置创建人的组织id
            lessonSchedule.setOrgId(one.getOrgId());

            // 9. 执行主表新增操作 (执行后 lessonSchedule.getId() 会自动回填)
            this.save(lessonSchedule);
        }

        // ================= 公共逻辑：同步子表数据 =================
        // 此时 lessonSchedule.getId() 一定有值 (无论是原有的还是新生成的)
        // 插入关联表lesson_schedule_setting数据，无论新增还是修改都需插入
        if (!CollectionUtils.isEmpty(lessonScheduleSettingList)) {
            ArrayList<LessonScheduleSetting> lessonScheduleSettings = new ArrayList<>();
            for (LessonScheduleSettingDTO lessonScheduleSettingDTO : lessonScheduleSettingList) {
                LessonScheduleSetting setting = BeanUtil.toBean(lessonScheduleSettingDTO, LessonScheduleSetting.class);
                // 关联主表 ID
                setting.setScheduleId(lessonSchedule.getId());
                lessonScheduleSettings.add(setting);
            }

            // 10. 批量插入子表数据
            lessonScheduleSettingService.saveBatch(lessonScheduleSettings);
        }


        // 返回主表 ID
        return JsonVO.success(lessonSchedule.getId());
    }

    /*
     * 根据排课计划id查询排课计划详情
     * */
    @Override
    public LessonScheduleVO getScheduleById(Long id) {
        // 1. 获取主表数据并转换 (保持原样，这行已经很简洁了)
        LessonSchedule byId = coursePlanService.getById(id);
        LessonScheduleVO lessonScheduleVO = BeanUtil.toBean(byId, LessonScheduleVO.class);

        // 2. 查询子表数据
        // 从lesson_schedule_setting表中查询数据
        List<LessonScheduleSetting> settings = lessonScheduleSettingService.list(
                new LambdaQueryWrapper<LessonScheduleSetting>()
                        .eq(LessonScheduleSetting::getScheduleId, id)
        );

        // 3. 【关键简化】使用 Stream 流一行完成 List 转换
        // 替换掉原来的 for 循环和 ArrayList 初始化
        List<LessonScheduleSettingDTO> settingDTOs = settings.stream()
                .map(s -> BeanUtil.toBean(s, LessonScheduleSettingDTO.class))
                .collect(Collectors.toList());

        // 如果 settings 为空，settingDTOs 也会是空列表，直接设进去没问题
        lessonScheduleVO.setSettingList(settingDTOs);
        return lessonScheduleVO;
    }

    /*
    * 根据id删除排课计划(支持批量删除)
    * */
    @Transactional
    @Override
    public List<Long> deleteSchedule(List<Long> ids) {
        // 1、根据传入的id查询表中数据
        List<LessonSchedule> lessonSchedules = coursePlanService.listByIds(ids);
        // 如果没有找到任何记录，直接返回空列表，无需执行删除
        if (lessonSchedules.isEmpty()){
            return new ArrayList<>();
        }

        // 2. 从查询结果中提取出真实的 ID (这些就是即将被删除的 ID)
        List<Long> realIds = lessonSchedules.stream()
                .map(LessonSchedule::getId)
                .collect(Collectors.toList());

        // 3、执行批量删除
        boolean delete = coursePlanService.removeByIds(realIds);

        // 4、同样执行批量删除关联表lesson_schedule_setting的数据
        LambdaQueryWrapper<LessonScheduleSetting> queryWrapper = new LambdaQueryWrapper<LessonScheduleSetting>()
                .in(LessonScheduleSetting::getScheduleId, realIds);
        lessonScheduleSettingService.remove(queryWrapper);

        if (delete){
            // 4、如果删除成功，则返回被删除的 ID
            return realIds;
        }
        else{
            throw new RuntimeException("删除失败");
        }
    }

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
