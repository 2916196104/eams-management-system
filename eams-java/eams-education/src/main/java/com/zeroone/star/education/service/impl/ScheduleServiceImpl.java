package com.zeroone.star.education.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.education.entity.LessonSchedule;
import com.zeroone.star.education.mapper.ScheduleMapper;
import com.zeroone.star.education.service.ScheduleService;
import com.zeroone.star.project.dto.j5.schedule.ScheduleSaveDTO;
import com.zeroone.star.project.query.j5.schedule.SchedulePlanQuery;
import com.zeroone.star.project.vo.j5.schedule.SchedulePlanVO;

public class ScheduleServiceImpl extends ServiceImpl<ScheduleMapper, LessonSchedule> implements ScheduleService {
    @Override
    public Page<SchedulePlanVO> listAll(SchedulePlanQuery query) {
        return null;
    }

    @Override
    public ScheduleSaveDTO getById(Long id) {
        return null;
    }
}
