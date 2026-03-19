package com.zeroone.star.j5.courseschedule.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j5.courseschedule.entity.Lesson;
import com.zeroone.star.j5.courseschedule.mapper.LessonMapper;
import com.zeroone.star.j5.courseschedule.service.ILessonService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonChangeStateDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonParamDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonSignSaveDTO;
import com.zeroone.star.project.vo.j5.courseschedule.LessonDetailVO;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * <p>
 * 描述：课次服务实现类
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
@Service
public class LessonServiceImpl extends ServiceImpl<LessonMapper, Lesson> implements ILessonService {

    @Override
    public PageDTO<?> queryList(LessonParamDTO param) {
        // TODO skeleton only: add real query logic in next stage
        return null;
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
    public LessonDetailVO queryDetail(Long lessonId) {
        // TODO skeleton only: add real detail query logic in next stage
        return null;
    }
}
