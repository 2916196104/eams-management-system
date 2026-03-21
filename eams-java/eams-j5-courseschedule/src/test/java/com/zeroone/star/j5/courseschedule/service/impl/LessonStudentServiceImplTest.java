package com.zeroone.star.j5.courseschedule.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j5.courseschedule.entity.LessonStudent;
import com.zeroone.star.j5.courseschedule.entity.StudentCourse;
import com.zeroone.star.j5.courseschedule.entity.StudentLessonCountLog;
import com.zeroone.star.j5.courseschedule.mapper.LessonStudentMapper;
import com.zeroone.star.j5.courseschedule.mapper.StudentCourseMapper;
import com.zeroone.star.j5.courseschedule.mapper.StudentLessonCountLogMapper;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonCountLogQueryDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonSignSaveDTO;
import com.zeroone.star.project.enums.SignStateEnum;
import com.zeroone.star.project.query.PageQuery;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static org.assertj.core.api.Assertions.assertThat;
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

    @InjectMocks
    private LessonStudentServiceImpl lessonStudentService;

    @Test
    void queryStatusList_shouldReturnPagedResults() {
        // Arrange
        PageQuery query = new PageQuery();
        query.setPageIndex(1L);
        query.setPageSize(10L);

        Map<String, Object> record = new HashMap<>();
        record.put("id", 1L);
        record.put("student_name", "张三");

        Page<Map<String, Object>> page = new Page<>(1, 10);
        page.setTotal(1);
        page.setRecords(new ArrayList<>(Arrays.asList(record)));

        when(baseMapper.selectStudentStatusPage(any(Page.class), eq("keyword"), eq("status")))
            .thenReturn(page);

        // Act
        PageDTO<Map<String, Object>> result = lessonStudentService.queryStatusList("keyword", "status", query);

        // Assert
        assertThat(result).isNotNull();
        assertThat(result.getTotal()).isEqualTo(1);
        assertThat(result.getRows()).hasSize(1);
    }

    @Test
    void queryStatusList_shouldUseDefaultPagination_whenQueryNull() {
        // Arrange
        Page<Map<String, Object>> page = new Page<>(1, 10);
        page.setTotal(0);
        page.setRecords(new ArrayList<>());

        when(baseMapper.selectStudentStatusPage(any(Page.class), any(), any()))
            .thenReturn(page);

        // Act
        PageDTO<Map<String, Object>> result = lessonStudentService.queryStatusList(null, null, null);

        // Assert
        assertThat(result).isNotNull();
        assertThat(result.getPageIndex()).isEqualTo(1);
        assertThat(result.getPageSize()).isEqualTo(10);
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
}
