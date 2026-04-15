package com.zeroone.star.j5.courseschedule.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j5.courseschedule.entity.LessonStudent;
import com.zeroone.star.j5.courseschedule.entity.StudentCourse;
import com.zeroone.star.j5.courseschedule.entity.StudentLessonCountLog;
import com.zeroone.star.j5.courseschedule.mapper.LessonMapper;
import com.zeroone.star.j5.courseschedule.mapper.LessonStudentMapper;
import com.zeroone.star.j5.courseschedule.mapper.StudentCourseMapper;
import com.zeroone.star.j5.courseschedule.mapper.StudentLessonCountLogMapper;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonCountLogQueryDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonSignSaveDTO;
import com.zeroone.star.project.enums.SignStateEnum;
import com.zeroone.star.project.query.j5.courseschedule.StudentStatusQuery;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.ArgumentCaptor;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.assertThatThrownBy;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.ArgumentMatchers.eq;
import static org.mockito.Mockito.*;

/**
 * LessonStudentServiceImpl 单元测试
 */
@ExtendWith(MockitoExtension.class)
class LessonStudentServiceImplTest {

    @Mock
    private LessonStudentMapper baseMapper;

    @Mock
    private StudentLessonCountLogMapper studentLessonCountLogMapper;

    @Mock
    private StudentCourseMapper studentCourseMapper;

    @Mock
    private LessonMapper lessonMapper;

    @InjectMocks
    private LessonStudentServiceImpl lessonStudentService;

    @Test
    void queryStatusList_shouldReturnPagedResults() {
        // Arrange
        StudentStatusQuery query = new StudentStatusQuery();
        query.setLessonId(1L);
        query.setPageIndex(1L);
        query.setPageSize(10L);
        query.setKeyword("keyword");
        query.setStatus("status");

        Map<String, Object> record = new HashMap<>();
        record.put("id", 1L);
        record.put("student_name", "张三");

        Page<Map<String, Object>> page = new Page<>(1, 10);
        page.setTotal(1);
        page.setRecords(new ArrayList<>(Arrays.asList(record)));

        when(baseMapper.selectStudentStatusPage(any(Page.class), eq(1L), eq("keyword"), eq("status")))
            .thenReturn(page);

        // Act
        PageDTO<Map<String, Object>> result = lessonStudentService.queryStatusList(query);

        // Assert
        assertThat(result).isNotNull();
        assertThat(result.getTotal()).isEqualTo(1);
        assertThat(result.getRows()).hasSize(1);
    }

    @Test
    void queryStatusList_shouldThrowException_whenQueryNull() {
        assertThatThrownBy(() -> lessonStudentService.queryStatusList(null))
                .isInstanceOf(RuntimeException.class)
                .hasMessageContaining("lessonId不能为空");
        verify(baseMapper, never()).selectStudentStatusPage(any(Page.class), any(), any(), any());
    }

    @Test
    void addOrUpdateRecord_shouldReturnAffectedRows_whenValidDto() {
        // Arrange
        LessonSignSaveDTO dto = new LessonSignSaveDTO();
        dto.setLessonId(1L);
        dto.setStudentId(100L);
        dto.setState(1); // 已签到
        dto.setSignType(1);

        LessonStudent lessonStudent = new LessonStudent();
        lessonStudent.setId(1L);

        when(baseMapper.selectByLessonAndStudent(1L, 100L)).thenReturn(lessonStudent);
        when(baseMapper.updateSignState(any(), any(), any(), any())).thenReturn(1);

        // Act
        Integer result = lessonStudentService.addOrUpdateRecord(dto);

        // Assert
        assertThat(result).isEqualTo(1);
        verify(baseMapper).updateSignState(eq(1L), eq(1), any(LocalDateTime.class), eq(1));
    }

    @Test
    void addOrUpdateRecord_shouldReturnZero_whenDtoNull() {
        // Act
        Integer result = lessonStudentService.addOrUpdateRecord(null);

        // Assert
        assertThat(result).isEqualTo(0);
    }

    @Test
    void addOrUpdateRecord_shouldReturnZero_whenLessonIdNull() {
        // Arrange
        LessonSignSaveDTO dto = new LessonSignSaveDTO();
        dto.setStudentId(100L);

        // Act
        Integer result = lessonStudentService.addOrUpdateRecord(dto);

        // Assert
        assertThat(result).isEqualTo(0);
    }

    @Test
    void addOrUpdateRecord_shouldReturnZero_whenStudentIdNull() {
        // Arrange
        LessonSignSaveDTO dto = new LessonSignSaveDTO();
        dto.setLessonId(1L);

        // Act
        Integer result = lessonStudentService.addOrUpdateRecord(dto);

        // Assert
        assertThat(result).isEqualTo(0);
    }

    @Test
    void addOrUpdateRecord_shouldReturnZero_whenSignStateInvalid() {
        // Arrange
        LessonSignSaveDTO dto = new LessonSignSaveDTO();
        dto.setLessonId(1L);
        dto.setStudentId(100L);
        dto.setState(99); // 无效状态

        // Act
        Integer result = lessonStudentService.addOrUpdateRecord(dto);

        // Assert
        assertThat(result).isEqualTo(0);
    }

    @Test
    void addOrUpdateRecord_shouldReturnZero_whenLessonStudentNotFound() {
        // Arrange
        LessonSignSaveDTO dto = new LessonSignSaveDTO();
        dto.setLessonId(1L);
        dto.setStudentId(100L);
        dto.setState(1);

        when(baseMapper.selectByLessonAndStudent(1L, 100L)).thenReturn(null);

        // Act
        Integer result = lessonStudentService.addOrUpdateRecord(dto);

        // Assert
        assertThat(result).isEqualTo(0);
    }

    @Test
    void batchAddOrUpdateRecord_shouldProcessAllRecords() {
        // Arrange
        LessonSignSaveDTO dto1 = new LessonSignSaveDTO();
        dto1.setLessonId(1L);
        dto1.setStudentId(100L);
        dto1.setState(1);

        LessonSignSaveDTO dto2 = new LessonSignSaveDTO();
        dto2.setLessonId(2L);
        dto2.setStudentId(101L);
        dto2.setState(2);

        LessonStudent ls1 = new LessonStudent();
        ls1.setId(1L);
        LessonStudent ls2 = new LessonStudent();
        ls2.setId(2L);

        when(baseMapper.selectByLessonAndStudent(1L, 100L)).thenReturn(ls1);
        when(baseMapper.selectByLessonAndStudent(2L, 101L)).thenReturn(ls2);
        when(baseMapper.updateSignState(any(), any(), any(), any())).thenReturn(1);

        // Act
        Integer result = lessonStudentService.batchAddOrUpdateRecord(Arrays.asList(dto1, dto2));

        // Assert
        assertThat(result).isEqualTo(2);
    }

    @Test
    void batchAddOrUpdateRecord_shouldReturnZero_whenListEmpty() {
        // Act
        Integer result = lessonStudentService.batchAddOrUpdateRecord(new ArrayList<>());

        // Assert
        assertThat(result).isEqualTo(0);
    }

    @Test
    void batchSetStatus_shouldReturnAffectedRows() {
        // Arrange
        List<Long> ids = Arrays.asList(1L, 2L, 3L);
        String status = "1"; // 已签到

        when(baseMapper.batchUpdateSignState(eq(ids), eq(1), any(LocalDateTime.class))).thenReturn(3);

        // Act
        Integer result = lessonStudentService.batchSetStatus(ids, status);

        // Assert
        assertThat(result).isEqualTo(3);
    }

    @Test
    void batchSetStatus_shouldReturnZero_whenIdsEmpty() {
        // Act
        Integer result = lessonStudentService.batchSetStatus(new ArrayList<>(), "1");

        // Assert
        assertThat(result).isEqualTo(0);
    }

    @Test
    void batchSetStatus_shouldReturnZero_whenStatusInvalid() {
        // Arrange
        List<Long> ids = Arrays.asList(1L, 2L);

        // Act
        Integer result = lessonStudentService.batchSetStatus(ids, "invalid");

        // Assert
        assertThat(result).isEqualTo(0);
    }

    @Test
    void batchSetStatus_shouldReturnZero_whenStatusCodeOutOfRange() {
        // Arrange
        List<Long> ids = Arrays.asList(1L, 2L);

        // Act
        Integer result = lessonStudentService.batchSetStatus(ids, "99");

        // Assert
        assertThat(result).isEqualTo(0);
        verify(baseMapper, never()).batchUpdateSignState(any(), any(), any());
    }

    @Test
    void rollbackCourseNum_shouldRestoreAndWriteLog() {
        // Arrange
        List<Long> ids = Arrays.asList(1L, 2L);

        LessonStudent ls1 = new LessonStudent();
        ls1.setId(1L);
        ls1.setStudentId(100L);
        ls1.setConsumeCourseId(10L);
        ls1.setConsumeStudentCourseId(1L);
        ls1.setDecLessonCount(2);

        LessonStudent ls2 = new LessonStudent();
        ls2.setId(2L);
        ls2.setStudentId(101L);
        ls2.setConsumeCourseId(11L);
        ls2.setConsumeStudentCourseId(2L);
        ls2.setDecLessonCount(1);

        StudentCourse sc = new StudentCourse();
        sc.setCountLessonTotal(20);
        sc.setCountLessonComplete(5);

        when(baseMapper.selectBatchIds(ids)).thenReturn(Arrays.asList(ls1, ls2));
        when(baseMapper.batchRestore(ids)).thenReturn(2);
        when(studentCourseMapper.rollBackLessonCount(any(), anyInt())).thenReturn(1);
        when(studentCourseMapper.selectById(any())).thenReturn(sc);

        // Act
        Integer result = lessonStudentService.rollbackCourseNum(ids);

        // Assert
        assertThat(result).isEqualTo(2);
        verify(studentLessonCountLogMapper, times(2)).insert(any(StudentLessonCountLog.class));
    }

    @Test
    void rollbackCourseNum_shouldReturnZero_whenIdsEmpty() {
        // Act
        Integer result = lessonStudentService.rollbackCourseNum(new ArrayList<>());

        // Assert
        assertThat(result).isEqualTo(0);
    }

    @Test
    void queryLessonCountLog_shouldReturnPagedLogs() {
        // Arrange
        LessonCountLogQueryDTO queryDTO = new LessonCountLogQueryDTO();
        queryDTO.setPageIndex(1L);
        queryDTO.setPageSize(10L);

        StudentLessonCountLog log = new StudentLessonCountLog();
        log.setId(1L);
        log.setStudentId(100L);

        Page<StudentLessonCountLog> page = new Page<>(1, 10);
        page.setTotal(1);
        page.setRecords(new ArrayList<>(Arrays.asList(log)));

        when(studentLessonCountLogMapper.selectLogPage(any(Page.class), any(), any(), any()))
            .thenReturn(page);

        // Act
        PageDTO<?> result = lessonStudentService.queryLessonCountLog(queryDTO);

        // Assert
        assertThat(result).isNotNull();
        assertThat(result.getTotal()).isEqualTo(1);
    }

    @Test
    void queryLessonCountLog_shouldUseDefaultPagination_whenQueryNull() {
        // Arrange
        Page<StudentLessonCountLog> page = new Page<>(1, 10);
        page.setTotal(0);
        page.setRecords(new ArrayList<>());

        when(studentLessonCountLogMapper.selectLogPage(any(Page.class), any(), any(), any()))
            .thenReturn(page);

        // Act
        PageDTO<?> result = lessonStudentService.queryLessonCountLog(null);

        // Assert
        assertThat(result).isNotNull();
        assertThat(result.getPageIndex()).isEqualTo(1);
        assertThat(result.getPageSize()).isEqualTo(10);
    }

    // ==================== pauseOrResumeLesson 停课/复课测试 ====================

    @Test
    void pauseOrResumeLesson_shouldResumeLesson_whenIsResumeTrue() {
        // Arrange
        List<Long> lessonIds = Arrays.asList(1L, 2L, 3L);
        List<Long> distinctLessonIds = lessonIds.stream().distinct().collect(Collectors.toList());
        Boolean isResume = true;

        // 复课时设置 lesson.state = 1 (进行中)
        when(lessonMapper.batchToggleStatus(eq(distinctLessonIds), eq(1))).thenReturn(3);
        // 复课时设置 sign_state = 0 (未签到) - 一个课次可能有多名学员，返回>=3都算成功
        when(baseMapper.batchUpdateSignStateByLessonIds(eq(distinctLessonIds), eq(0)))
            .thenReturn(3);

        // Act
        Integer result = lessonStudentService.pauseOrResumeLesson(lessonIds, isResume);

        // Assert
        assertThat(result).isEqualTo(3);
        verify(lessonMapper).batchToggleStatus(eq(distinctLessonIds), eq(1));
        verify(baseMapper).batchUpdateSignStateByLessonIds(eq(distinctLessonIds), eq(0));
    }

    @Test
    void pauseOrResumeLesson_shouldPauseLesson_whenIsResumeFalse() {
        // Arrange
        List<Long> lessonIds = Arrays.asList(1L, 2L);
        List<Long> distinctLessonIds = lessonIds.stream().distinct().collect(Collectors.toList());
        Boolean isResume = false;

        // 停课时设置 lesson.state = 0 (已停课)
        when(lessonMapper.batchToggleStatus(eq(distinctLessonIds), eq(0))).thenReturn(2);
        // 停课时设置 sign_state = 4 (旷课) - 一个课次可能有多名学员，返回>=2都算成功
        when(baseMapper.batchUpdateSignStateByLessonIds(eq(distinctLessonIds), eq(4)))
            .thenReturn(2);

        // Act
        Integer result = lessonStudentService.pauseOrResumeLesson(lessonIds, isResume);

        // Assert
        assertThat(result).isEqualTo(2);
        verify(lessonMapper).batchToggleStatus(eq(distinctLessonIds), eq(0));
        verify(baseMapper).batchUpdateSignStateByLessonIds(eq(distinctLessonIds), eq(4));
    }

    @Test
    void pauseOrResumeLesson_shouldResumeLesson_whenIsResumeNull() {
        // Arrange
        List<Long> lessonIds = Arrays.asList(1L);
        List<Long> distinctLessonIds = lessonIds.stream().distinct().collect(Collectors.toList());
        Boolean isResume = null;

        // isResume 为 null 时，按 false 处理（停课，设置 lesson.state = 0, sign_state = 4）
        when(lessonMapper.batchToggleStatus(eq(distinctLessonIds), eq(0))).thenReturn(1);
        when(baseMapper.batchUpdateSignStateByLessonIds(eq(distinctLessonIds), eq(4)))
            .thenReturn(1);

        // Act
        Integer result = lessonStudentService.pauseOrResumeLesson(lessonIds, isResume);

        // Assert
        assertThat(result).isEqualTo(1);
        verify(lessonMapper).batchToggleStatus(eq(distinctLessonIds), eq(0));
        verify(baseMapper).batchUpdateSignStateByLessonIds(eq(distinctLessonIds), eq(4));
    }

    @Test
    void pauseOrResumeLesson_shouldReturnZero_whenLessonIdsEmpty() {
        // Act
        Integer result = lessonStudentService.pauseOrResumeLesson(new ArrayList<>(), true);

        // Assert
        assertThat(result).isEqualTo(0);
        verify(baseMapper, never()).batchUpdateSignStateByLessonIds(any(), any());
    }

    @Test
    void pauseOrResumeLesson_shouldReturnZero_whenLessonIdsNull() {
        // Act
        Integer result = lessonStudentService.pauseOrResumeLesson(null, true);

        // Assert
        assertThat(result).isEqualTo(0);
        verify(baseMapper, never()).batchUpdateSignStateByLessonIds(any(), any());
    }

    // ==================== 补充边界条件测试 ====================

    @Test
    void queryStatusList_shouldWorkWithLessonIdFilter() {
        // Arrange - 使用 StudentStatusQuery（包含 lessonId）
        StudentStatusQuery query = new StudentStatusQuery();
        query.setPageIndex(1L);
        query.setPageSize(20L);
        query.setLessonId(100L);

        Map<String, Object> record = new HashMap<>();
        record.put("id", 1L);
        record.put("student_name", "李四");

        Page<Map<String, Object>> page = new Page<>(1, 20);
        page.setTotal(1);
        page.setRecords(new ArrayList<>(Arrays.asList(record)));

        // 传入的 keyword 和 status 为 null，lessonId 为 100L
        when(baseMapper.selectStudentStatusPage(any(Page.class), eq(100L), isNull(), isNull()))
            .thenReturn(page);

        // Act
        PageDTO<Map<String, Object>> result = lessonStudentService.queryStatusList(query);

        // Assert
        assertThat(result).isNotNull();
        assertThat(result.getTotal()).isEqualTo(1);
        assertThat(result.getRows()).hasSize(1);
        verify(baseMapper).selectStudentStatusPage(any(Page.class), eq(100L), isNull(), isNull());
    }

    @Test
    void queryStatusList_shouldWorkWithKeywordAndStatus() {
        // Arrange - 使用带 keyword 和 status 的查询
        StudentStatusQuery query = new StudentStatusQuery();
        query.setPageIndex(1L);
        query.setPageSize(10L);
        query.setLessonId(100L);
        query.setKeyword("张三");
        query.setStatus("1");

        Map<String, Object> record = new HashMap<>();
        record.put("id", 1L);
        record.put("student_name", "张三");

        Page<Map<String, Object>> page = new Page<>(1, 10);
        page.setTotal(1);
        page.setRecords(new ArrayList<>(Arrays.asList(record)));

        when(baseMapper.selectStudentStatusPage(any(Page.class), eq(100L), eq("张三"), eq("1")))
            .thenReturn(page);

        // Act
        PageDTO<Map<String, Object>> result = lessonStudentService.queryStatusList(query);

        // Assert
        assertThat(result).isNotNull();
        assertThat(result.getTotal()).isEqualTo(1);
        assertThat(result.getRows()).hasSize(1);
        verify(baseMapper).selectStudentStatusPage(any(Page.class), eq(100L), eq("张三"), eq("1"));
    }

    @Test
    void rollbackCourseNum_shouldReturnZero_whenSelectBatchIdsReturnsEmptyList() {
        // Arrange
        List<Long> ids = Arrays.asList(1L, 2L);

        when(baseMapper.selectBatchIds(ids)).thenReturn(new ArrayList<>());

        // Act
        Integer result = lessonStudentService.rollbackCourseNum(ids);

        // Assert
        assertThat(result).isEqualTo(0);
        verify(baseMapper, never()).batchRestore(any());
        verify(studentCourseMapper, never()).rollBackLessonCount(any(), anyInt());
    }

    @Test
    void batchSetStatus_shouldReturnZero_whenStatusNull() {
        // Arrange
        List<Long> ids = Arrays.asList(1L, 2L);

        // Act
        Integer result = lessonStudentService.batchSetStatus(ids, null);

        // Assert
        assertThat(result).isEqualTo(0);
        verify(baseMapper, never()).batchUpdateSignState(any(), any(), any());
    }

    @Test
    void batchSetStatus_shouldReturnZero_whenStatusBlank() {
        // Arrange
        List<Long> ids = Arrays.asList(1L, 2L);

        // Act
        Integer result = lessonStudentService.batchSetStatus(ids, "   ");

        // Assert
        assertThat(result).isEqualTo(0);
        verify(baseMapper, never()).batchUpdateSignState(any(), any(), any());
    }

    @Test
    void batchSetStatus_shouldWorkWithEnumName() {
        // Arrange - 使用枚举名称设置状态
        List<Long> ids = Arrays.asList(1L);
        String status = "NORMAL"; // 已签到

        when(baseMapper.batchUpdateSignState(eq(ids), eq(1), any(LocalDateTime.class))).thenReturn(1);

        // Act
        Integer result = lessonStudentService.batchSetStatus(ids, status);

        // Assert
        assertThat(result).isEqualTo(1);
        verify(baseMapper).batchUpdateSignState(eq(ids), eq(1), any(LocalDateTime.class));
    }

    @Test
    void batchSetStatus_shouldWorkWithEnumNameLowerCase() {
        // Arrange - 使用小写枚举名称
        List<Long> ids = Arrays.asList(1L);
        String status = "leave"; // 请假

        when(baseMapper.batchUpdateSignState(eq(ids), eq(3), any(LocalDateTime.class))).thenReturn(1);

        // Act
        Integer result = lessonStudentService.batchSetStatus(ids, status);

        // Assert
        assertThat(result).isEqualTo(1);
        verify(baseMapper).batchUpdateSignState(eq(ids), eq(3), any(LocalDateTime.class));
    }

    @Test
    void batchSetStatus_shouldReturnZero_whenIdsNull() {
        // Act
        Integer result = lessonStudentService.batchSetStatus(null, "1");

        // Assert
        assertThat(result).isEqualTo(0);
        verify(baseMapper, never()).batchUpdateSignState(any(), any(), any());
    }

    // ==================== pauseOrResumeLesson 失败路径测试 ====================

    @Test
    void pauseOrResumeLesson_shouldThrowException_whenLessonMapperReturnsZero() {
        // Arrange - lessonMapper 返回 0（失败），应抛出异常并阻止后续操作
        List<Long> lessonIds = Arrays.asList(1L, 2L);
        Boolean isResume = true;
        List<Long> distinctLessonIds = lessonIds.stream().distinct().collect(Collectors.toList());

        // lessonMapper 更新失败，返回 0
        when(lessonMapper.batchToggleStatus(eq(distinctLessonIds), eq(1))).thenReturn(0);

        // Act & Assert - 应抛出异常，不会继续调用 baseMapper
        assertThatThrownBy(() -> lessonStudentService.pauseOrResumeLesson(lessonIds, isResume))
                .isInstanceOf(RuntimeException.class)
                .hasMessageContaining("课次状态更新失败");
        verify(lessonMapper).batchToggleStatus(eq(distinctLessonIds), eq(1));
        verify(baseMapper, never()).batchUpdateSignStateByLessonIds(any(), any());
    }

    @Test
    void pauseOrResumeLesson_shouldThrowException_whenBaseMapperPartialFailure() {
        // Arrange - 第一步成功，但第二步部分失败，应抛出异常
        List<Long> lessonIds = Arrays.asList(1L, 2L, 3L);
        Boolean isResume = false;
        List<Long> distinctLessonIds = lessonIds.stream().distinct().collect(Collectors.toList());

        // lessonMapper 成功更新 3 条
        when(lessonMapper.batchToggleStatus(eq(distinctLessonIds), eq(0))).thenReturn(3);
        // 但 baseMapper 只成功更新 1 条（模拟部分失败场景，1 < 3）
        when(baseMapper.batchUpdateSignStateByLessonIds(eq(distinctLessonIds), eq(4))).thenReturn(1);

        // Act & Assert - 应抛出异常
        assertThatThrownBy(() -> lessonStudentService.pauseOrResumeLesson(lessonIds, isResume))
                .isInstanceOf(RuntimeException.class)
                .hasMessageContaining("学员签到状态更新失败");
    }

    // ==================== 分页参数精确校验测试 ====================

    @Test
    void queryStatusList_shouldPassCorrectPageIndexAndSize() {
        // Arrange
        StudentStatusQuery query = new StudentStatusQuery();
        query.setLessonId(200L);
        query.setPageIndex(3L);
        query.setPageSize(20L);

        Page<Map<String, Object>> page = new Page<>(3, 20);
        page.setTotal(0);
        page.setRecords(new ArrayList<>());

        // 精确捕获 Page 参数
        ArgumentCaptor<Page> pageCaptor = ArgumentCaptor.forClass(Page.class);
        when(baseMapper.selectStudentStatusPage(pageCaptor.capture(), any(), any(), any()))
            .thenReturn(page);

        // Act
        PageDTO<Map<String, Object>> result = lessonStudentService.queryStatusList(query);

        // Assert - 验证分页参数正确传递
        Page<Map<String, Object>> capturedPage = pageCaptor.getValue();
        assertThat(capturedPage.getCurrent()).isEqualTo(3L);
        assertThat(capturedPage.getSize()).isEqualTo(20L);
    }

    @Test
    void queryStatusList_shouldUseDefaultPageIndex_whenZero() {
        // Arrange - pageIndex 为 0 时应使用默认值 1
        StudentStatusQuery query = new StudentStatusQuery();
        query.setLessonId(200L);
        query.setPageIndex(0L);
        query.setPageSize(10L);

        Page<Map<String, Object>> page = new Page<>(1, 10);
        page.setTotal(0);
        page.setRecords(new ArrayList<>());

        ArgumentCaptor<Page> pageCaptor = ArgumentCaptor.forClass(Page.class);
        when(baseMapper.selectStudentStatusPage(pageCaptor.capture(), any(), any(), any()))
            .thenReturn(page);

        // Act
        PageDTO<Map<String, Object>> result = lessonStudentService.queryStatusList(query);

        // Assert
        Page<Map<String, Object>> capturedPage = pageCaptor.getValue();
        assertThat(capturedPage.getCurrent()).isEqualTo(1L);
        assertThat(capturedPage.getSize()).isEqualTo(10L);
    }

    @Test
    void queryStatusList_shouldUseDefaultPageSize_whenNegative() {
        // Arrange - pageSize 为负数时应使用默认值 10
        StudentStatusQuery query = new StudentStatusQuery();
        query.setLessonId(200L);
        query.setPageIndex(1L);
        query.setPageSize(-5L);

        Page<Map<String, Object>> page = new Page<>(1, 10);
        page.setTotal(0);
        page.setRecords(new ArrayList<>());

        ArgumentCaptor<Page> pageCaptor = ArgumentCaptor.forClass(Page.class);
        when(baseMapper.selectStudentStatusPage(pageCaptor.capture(), any(), any(), any()))
            .thenReturn(page);

        // Act
        PageDTO<Map<String, Object>> result = lessonStudentService.queryStatusList(query);

        // Assert
        Page<Map<String, Object>> capturedPage = pageCaptor.getValue();
        assertThat(capturedPage.getCurrent()).isEqualTo(1L);
        assertThat(capturedPage.getSize()).isEqualTo(10L);
    }

    // ==================== rollbackCourseNum 参数断言测试 ====================

    @Test
    void rollbackCourseNum_shouldPassCorrectRollbackCount() {
        // Arrange
        List<Long> ids = Arrays.asList(1L, 2L);

        LessonStudent ls1 = new LessonStudent();
        ls1.setId(1L);
        ls1.setStudentId(100L);
        ls1.setConsumeCourseId(10L);
        ls1.setConsumeStudentCourseId(1L);
        ls1.setDecLessonCount(2);  // 应回退 2 课时

        LessonStudent ls2 = new LessonStudent();
        ls2.setId(2L);
        ls2.setStudentId(101L);
        ls2.setConsumeCourseId(11L);
        ls2.setConsumeStudentCourseId(2L);
        ls2.setDecLessonCount(3);  // 应回退 3 课时

        StudentCourse sc = new StudentCourse();
        sc.setCountLessonTotal(20);
        sc.setCountLessonComplete(5);

        when(baseMapper.selectBatchIds(ids)).thenReturn(Arrays.asList(ls1, ls2));
        when(baseMapper.batchRestore(ids)).thenReturn(2);

        // 精确捕获 rollBackLessonCount 参数
        ArgumentCaptor<Integer> countCaptor = ArgumentCaptor.forClass(Integer.class);
        when(studentCourseMapper.rollBackLessonCount(any(), countCaptor.capture())).thenReturn(1);
        when(studentCourseMapper.selectById(any())).thenReturn(sc);

        // Act
        Integer result = lessonStudentService.rollbackCourseNum(ids);

        // Assert - 验证回退课时数正确
        assertThat(result).isEqualTo(2);
        // 验证 decLessonCount 被正确传递
        List<Integer> capturedCounts = countCaptor.getAllValues();
        assertThat(capturedCounts).containsExactlyInAnyOrder(2, 3);
    }

    @Test
    void rollbackCourseNum_shouldNotRollback_whenDecLessonCountIsZero() {
        // Arrange - decLessonCount 为 0 时不应回退
        List<Long> ids = Arrays.asList(1L);

        LessonStudent ls1 = new LessonStudent();
        ls1.setId(1L);
        ls1.setStudentId(100L);
        ls1.setConsumeCourseId(10L);
        ls1.setConsumeStudentCourseId(1L);
        ls1.setDecLessonCount(0);  // 0 课时不应回退

        when(baseMapper.selectBatchIds(ids)).thenReturn(Arrays.asList(ls1));
        when(baseMapper.batchRestore(ids)).thenReturn(1);

        // Act
        Integer result = lessonStudentService.rollbackCourseNum(ids);

        // Assert - 虽然调用了 batchRestore，但不应调用 rollBackLessonCount
        assertThat(result).isEqualTo(1);
        verify(studentCourseMapper, never()).rollBackLessonCount(any(), anyInt());
    }
}
