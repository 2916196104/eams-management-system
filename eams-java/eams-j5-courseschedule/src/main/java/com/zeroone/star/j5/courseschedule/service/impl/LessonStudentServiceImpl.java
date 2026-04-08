package com.zeroone.star.j5.courseschedule.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j5.courseschedule.entity.LessonStudent;
import com.zeroone.star.j5.courseschedule.entity.StudentCourse;
import com.zeroone.star.j5.courseschedule.entity.StudentLessonCountLog;
import com.zeroone.star.j5.courseschedule.mapper.LessonMapper;
import com.zeroone.star.j5.courseschedule.mapper.LessonStudentMapper;
import com.zeroone.star.j5.courseschedule.mapper.StudentCourseMapper;
import com.zeroone.star.j5.courseschedule.mapper.StudentLessonCountLogMapper;
import com.zeroone.star.j5.courseschedule.service.ILessonStudentService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonCountLogQueryDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonSignSaveDTO;
import com.zeroone.star.project.enums.LessonCountChangeStageEnum;
import com.zeroone.star.project.enums.SignStateEnum;
import com.zeroone.star.project.query.j5.courseschedule.StudentStatusQuery;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.stream.Collectors;

@Service
public class LessonStudentServiceImpl extends ServiceImpl<LessonStudentMapper, LessonStudent> implements ILessonStudentService {

    @Resource
    private StudentLessonCountLogMapper studentLessonCountLogMapper;

    @Resource
    private StudentCourseMapper studentCourseMapper;

    @Resource
    private LessonMapper lessonMapper;

    @Override
    public PageDTO<Map<String, Object>> queryStatusList(StudentStatusQuery query) {
        if (query == null || query.getLessonId() == null) {
            throw new RuntimeException("lessonId不能为空");
        }
        long pageIndex = query.getPageIndex() > 0 ? query.getPageIndex() : 1L;
        long pageSize = query.getPageSize() > 0 ? query.getPageSize() : 10L;

        // 从 query 对象中提取 lessonId
        Long lessonId = query.getLessonId();
        String keyword = query.getKeyword();
        String status = query.getStatus();

        Page<Map<String, Object>> page = new Page<>(pageIndex, pageSize);
        IPage<Map<String, Object>> result = baseMapper.selectStudentStatusPage(page, lessonId, keyword, status);
        return toPageDTO(result);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Integer addOrUpdateRecord(LessonSignSaveDTO dto) {
        if (dto == null || dto.getLessonId() == null || dto.getStudentId() == null) {
            return 0;
        }

        SignStateEnum signStateEnum = SignStateEnum.getByCode(dto.getState());
        if (signStateEnum == null) {
            return 0;
        }

        LessonStudent lessonStudent = baseMapper.selectByLessonAndStudent(dto.getLessonId(), dto.getStudentId());
        if (lessonStudent == null) {
            return 0;
        }

        return baseMapper.updateSignState(
                lessonStudent.getId(),
                signStateEnum.getCode(),
                LocalDateTime.now(),
                dto.getSignType()
        );
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Integer batchAddOrUpdateRecord(List<LessonSignSaveDTO> dtoList) {
        if (dtoList == null || dtoList.isEmpty()) {
            return 0;
        }

        int affected = 0;
        for (LessonSignSaveDTO dto : dtoList) {
            affected += addOrUpdateRecord(dto);
        }
        return affected;
    }

    @Override
    public Integer batchSetStatus(List<Long> lessonStudentIds, String status) {
        if (lessonStudentIds == null || lessonStudentIds.isEmpty()) {
            return 0;
        }

        Integer signState = convertStatusToCode(status);
        if (signState == null) {
            return 0;
        }

        return baseMapper.batchUpdateSignState(lessonStudentIds, signState, LocalDateTime.now());
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Integer rollbackCourseNum(List<Long> lessonStudentIds) {
        if (lessonStudentIds == null || lessonStudentIds.isEmpty()) {
            return 0;
        }

        List<LessonStudent> lessonStudents = baseMapper.selectBatchIds(lessonStudentIds);
        if (lessonStudents == null || lessonStudents.isEmpty()) {
            return 0;
        }

        int restoredRows = baseMapper.batchRestore(lessonStudentIds);
        for (LessonStudent lessonStudent : lessonStudents) {
            rollbackStudentCourseAndWriteLog(lessonStudent);
        }
        return restoredRows;
    }

    @Override
    public PageDTO<?> queryLessonCountLog(LessonCountLogQueryDTO queryDTO) {
        LessonCountLogQueryDTO safeQuery = queryDTO == null ? new LessonCountLogQueryDTO() : queryDTO;
        long pageIndex = safeQuery.getPageIndex() > 0 ? safeQuery.getPageIndex() : 1L;
        long pageSize = safeQuery.getPageSize() > 0 ? safeQuery.getPageSize() : 10L;

        Page<StudentLessonCountLog> page = new Page<>(pageIndex, pageSize);
        IPage<StudentLessonCountLog> result = studentLessonCountLogMapper.selectLogPage(
                page,
                safeQuery.getStudentId(),
                safeQuery.getCourseId(),
                safeQuery.getStage()
        );

        return toPageDTO(result);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Integer pauseOrResumeLesson(List<Long> lessonIds, Boolean isResume) {
        if (lessonIds == null || lessonIds.isEmpty()) {
            return 0;
        }

        // isResume = true: 复课，设置lesson.state=1(进行中)，学员签到状态=0(未签到)
        // isResume = false: 停课，设置lesson.state=0(已停课)，学员签到状态=4(旷课)
        Integer targetSignState = Boolean.TRUE.equals(isResume)
                ? SignStateEnum.NONE.getCode()   // 0-未签到
                : SignStateEnum.ABSENT.getCode();     // 4-旷课

        Integer targetLessonState = Boolean.TRUE.equals(isResume) ? 1 : 0;  // 1-进行中, 0-已停课

        // 去重后的课次ID数量（应对重复ID入参）
        List<Long> distinctLessonIds = lessonIds.stream().distinct().collect(Collectors.toList());
        int distinctCount = distinctLessonIds.size();

        // 第一步：更新课次状态，并校验影响行数
        int lessonUpdatedRows = lessonMapper.batchToggleStatus(distinctLessonIds, targetLessonState);
        if (lessonUpdatedRows != distinctCount) {
            throw new RuntimeException("课次状态更新失败，预期更新" + distinctCount + "行，实际更新" + lessonUpdatedRows + "行");
        }

        // 第二步：更新学员签到状态（不更新sign_time，仅更新签到状态）
        // 注意：一个课次可能有多名学员，所以 signUpdatedRows >= distinctCount 才算成功
        int signUpdatedRows = baseMapper.batchUpdateSignStateByLessonIds(distinctLessonIds, targetSignState);
        if (signUpdatedRows < distinctCount) {
            throw new RuntimeException("学员签到状态更新失败，预期更新至少" + distinctCount + "行，实际更新" + signUpdatedRows + "行");
        }

        return distinctCount;
    }

    private void rollbackStudentCourseAndWriteLog(LessonStudent lessonStudent) {
        if (lessonStudent == null || lessonStudent.getConsumeStudentCourseId() == null) {
            return;
        }

        int rollbackCount = resolveRollbackCount(lessonStudent);
        if (rollbackCount <= 0) {
            return;
        }

        int affected = studentCourseMapper.rollBackLessonCount(lessonStudent.getConsumeStudentCourseId(), rollbackCount);
        if (affected <= 0) {
            return;
        }

        StudentCourse studentCourse = studentCourseMapper.selectById(lessonStudent.getConsumeStudentCourseId());
        StudentLessonCountLog log = new StudentLessonCountLog();
        if (lessonStudent.getStudentId() == null || lessonStudent.getConsumeCourseId() == null) {
            return;
        }
        log.setStudentId(lessonStudent.getStudentId());
        log.setCourseId(lessonStudent.getConsumeCourseId());
        log.setLessonId(lessonStudent.getLessonId());
        log.setChangeCount(rollbackCount);
        if (studentCourse != null
                && studentCourse.getCountLessonTotal() != null
                && studentCourse.getCountLessonComplete() != null) {
            log.setRemainingCount(studentCourse.getCountLessonTotal() - studentCourse.getCountLessonComplete());
        }
        log.setAddTime(LocalDateTime.now());
        log.setStage(LessonCountChangeStageEnum.ROLLBACK.getCode());
        log.setRemark("Rollback lesson progress");
        studentLessonCountLogMapper.insert(log);
    }

    private int resolveRollbackCount(LessonStudent lessonStudent) {
        // 只使用 decLessonCount 进行还原，避免重复还原
        // batchRestore 后 decLessonCount 会被置为 0，防止再次还原
        Integer decLessonCount = lessonStudent.getDecLessonCount();
        if (decLessonCount != null && decLessonCount > 0) {
            return decLessonCount;
        }
        // decLessonCount 为 0 或 null 时，不允许还原（防止重复还原）
        return 0;
    }

    private Integer convertStatusToCode(String status) {
        if (isBlank(status)) {
            return null;
        }

        try {
            int code = Integer.parseInt(status);
            SignStateEnum signStateEnum = SignStateEnum.getByCode(code);
            return signStateEnum == null ? null : signStateEnum.getCode();
        } catch (NumberFormatException ignored) {
            String normalized = status.trim().toUpperCase(Locale.ROOT);
            for (SignStateEnum stateEnum : SignStateEnum.values()) {
                if (stateEnum.name().equals(normalized)) {
                    return stateEnum.getCode();
                }
            }
        }
        return null;
    }

    private boolean isBlank(String value) {
        return value == null || value.trim().isEmpty();
    }

    private <T> PageDTO<T> toPageDTO(IPage<T> page) {
        PageDTO<T> pageDTO = new PageDTO<>();
        pageDTO.setTotal(page.getTotal());
        pageDTO.setPageIndex(page.getCurrent());
        pageDTO.setPageSize(page.getSize());
        pageDTO.setPages(page.getPages());
        pageDTO.setRows(page.getRecords());
        return pageDTO;
    }
}
