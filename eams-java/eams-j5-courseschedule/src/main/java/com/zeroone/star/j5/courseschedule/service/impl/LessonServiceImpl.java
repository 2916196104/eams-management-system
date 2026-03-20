package com.zeroone.star.j5.courseschedule.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j5.courseschedule.entity.Lesson;
import com.zeroone.star.j5.courseschedule.mapper.LessonMapper;
import com.zeroone.star.j5.courseschedule.service.ILessonService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonChangeStateDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonParamDTO;
import com.zeroone.star.project.enums.LessonStateEnum;
import com.zeroone.star.project.vo.j5.courseschedule.LessonDetailVO;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;

@Service
public class LessonServiceImpl extends ServiceImpl<LessonMapper, Lesson> implements ILessonService {

    @Override
    public PageDTO<?> queryList(LessonParamDTO param) {
        LessonParamDTO safeParam = param == null ? new LessonParamDTO() : param;
        long pageIndex = safeParam.getPageIndex() > 0 ? safeParam.getPageIndex() : 1L;
        long pageSize = safeParam.getPageSize() > 0 ? safeParam.getPageSize() : 10L;

        Page<Lesson> page = new Page<>(pageIndex, pageSize);
        IPage<Lesson> result = baseMapper.selectLessonPage(page, safeParam);
        return toPageDTO(result);
    }

    @Override
    public Integer changeLessonState(LessonChangeStateDTO dto) {
        if (dto == null || dto.getLessonIds() == null || dto.getLessonIds().isEmpty()) {
            return 0;
        }
        Integer targetState = dto.getTargetState();
        if (targetState == null || !isValidState(targetState)) {
            return 0;
        }
        return baseMapper.batchToggleStatus(dto.getLessonIds(), targetState);
    }

    @Override
    public LessonDetailVO queryDetail(Long lessonId) {
        if (lessonId == null) {
            return null;
        }
        Lesson lesson = baseMapper.selectById(lessonId);
        if (lesson == null) {
            return null;
        }
        LessonDetailVO vo = new LessonDetailVO();
        BeanUtils.copyProperties(lesson, vo);
        vo.setLessonId(lesson.getId()); // BeanUtils不会自动映射不同名字的字段
        return vo;
    }

    private boolean isValidState(Integer state) {
        return LessonStateEnum.STOPPED.getCode().equals(state)
                || LessonStateEnum.UNDERWAY.getCode().equals(state)
                || LessonStateEnum.COMPLETE.getCode().equals(state);
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
