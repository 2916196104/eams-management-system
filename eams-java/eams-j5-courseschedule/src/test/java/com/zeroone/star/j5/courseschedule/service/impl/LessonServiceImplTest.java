package com.zeroone.star.j5.courseschedule.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j5.courseschedule.entity.Lesson;
import com.zeroone.star.j5.courseschedule.mapper.LessonMapper;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonChangeStateDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonParamDTO;
import com.zeroone.star.project.vo.j5.courseschedule.LessonDetailVO;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.ArgumentCaptor;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static org.assertj.core.api.Assertions.assertThat;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.ArgumentMatchers.eq;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

/**
 * LessonServiceImpl 单元测试
 */
@ExtendWith(MockitoExtension.class)
class LessonServiceImplTest {

    @Mock
    private LessonMapper lessonMapper;

    @InjectMocks
    private LessonServiceImpl lessonService;

    @Test
    void queryList_shouldReturnPagedResults() {
        // Arrange
        LessonParamDTO param = new LessonParamDTO();
        param.setPageIndex(1L);
        param.setPageSize(10L);

        Lesson lesson = new Lesson();
        lesson.setId(1L);
        lesson.setTitle("数学课");

        Page<Lesson> page = new Page<>(1, 10);
        page.setTotal(1);
        page.setRecords(new ArrayList<>(Arrays.asList(lesson)));

        when(lessonMapper.selectLessonPage(any(Page.class), eq(param))).thenReturn(page);

        // Act
        PageDTO<?> result = lessonService.queryList(param);

        // Assert
        assertThat(result).isNotNull();
        assertThat(result.getTotal()).isEqualTo(1);
        assertThat(result.getRows()).hasSize(1);
    }

    @Test
    void queryList_shouldUseDefaultPagination_whenParamsNull() {
        // Arrange
        LessonParamDTO param = null;

        Page<Lesson> page = new Page<>(1, 10);
        page.setTotal(0);
        page.setRecords(new ArrayList<>());

        when(lessonMapper.selectLessonPage(any(Page.class), any(LessonParamDTO.class))).thenReturn(page);

        // Act
        PageDTO<?> result = lessonService.queryList(param);

        // Assert
        assertThat(result).isNotNull();
        assertThat(result.getPageIndex()).isEqualTo(1);
        assertThat(result.getPageSize()).isEqualTo(10);
    }

    @Test
    void queryList_shouldParseDateRange_whenStartAndEndDateAbsent() {
        // Arrange
        LessonParamDTO param = new LessonParamDTO();
        param.setDateRange("2026-03-01,2026-03-10");

        Page<Lesson> page = new Page<>(1, 10);
        page.setTotal(0);
        page.setRecords(new ArrayList<>());
        when(lessonMapper.selectLessonPage(any(Page.class), any(LessonParamDTO.class))).thenReturn(page);

        // Act
        lessonService.queryList(param);

        // Assert
        ArgumentCaptor<LessonParamDTO> captor = ArgumentCaptor.forClass(LessonParamDTO.class);
        verify(lessonMapper).selectLessonPage(any(Page.class), captor.capture());
        LessonParamDTO passed = captor.getValue();
        assertThat(passed.getStartDate()).isEqualTo(LocalDate.parse("2026-03-01"));
        assertThat(passed.getEndDate()).isEqualTo(LocalDate.parse("2026-03-10"));
    }

    @Test
    void changeLessonState_shouldReturnAffectedRows() {
        // Arrange
        LessonChangeStateDTO dto = new LessonChangeStateDTO();
        dto.setLessonIds(Arrays.asList(1L, 2L, 3L));
        dto.setTargetState(0); // 停课

        when(lessonMapper.batchToggleStatus(dto.getLessonIds(), dto.getTargetState()))
            .thenReturn(3);

        // Act
        Integer result = lessonService.changeLessonState(dto);

        // Assert
        assertThat(result).isEqualTo(3);
    }

    @Test
    void changeLessonState_shouldReturnZero_whenDtoNull() {
        // Act
        Integer result = lessonService.changeLessonState(null);

        // Assert
        assertThat(result).isEqualTo(0);
    }

    @Test
    void changeLessonState_shouldReturnZero_whenLessonIdsEmpty() {
        // Arrange
        LessonChangeStateDTO dto = new LessonChangeStateDTO();
        dto.setLessonIds(new ArrayList<>());
        dto.setTargetState(0);

        // Act
        Integer result = lessonService.changeLessonState(dto);

        // Assert
        assertThat(result).isEqualTo(0);
    }

    @Test
    void changeLessonState_shouldReturnZero_whenTargetStateInvalid() {
        // Arrange
        LessonChangeStateDTO dto = new LessonChangeStateDTO();
        dto.setLessonIds(Arrays.asList(1L, 2L));
        dto.setTargetState(99); // 无效状态

        // Act
        Integer result = lessonService.changeLessonState(dto);

        // Assert
        assertThat(result).isEqualTo(0);
    }

    @Test
    void queryDetail_shouldReturnLessonDetail() {
        // Arrange
        Long lessonId = 1L;
        Lesson lesson = new Lesson();
        lesson.setId(lessonId);
        lesson.setTitle("数学课");
        lesson.setSn(1);
        lesson.setState(1);

        when(lessonMapper.selectById(lessonId)).thenReturn(lesson);

        // Act
        LessonDetailVO result = lessonService.queryDetail(lessonId);

        // Assert
        assertThat(result).isNotNull();
        assertThat(result.getLessonId()).isEqualTo(lessonId);
        assertThat(result.getTitle()).isEqualTo("数学课");
    }

    @Test
    void queryDetail_shouldReturnNull_whenLessonNotFound() {
        // Arrange
        Long lessonId = 999L;
        when(lessonMapper.selectById(lessonId)).thenReturn(null);

        // Act
        LessonDetailVO result = lessonService.queryDetail(lessonId);

        // Assert
        assertThat(result).isNull();
    }

    @Test
    void queryDetail_shouldReturnNull_whenLessonIdNull() {
        // Act
        LessonDetailVO result = lessonService.queryDetail(null);

        // Assert
        assertThat(result).isNull();
    }
}
