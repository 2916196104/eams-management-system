package com.zeroone.star.education.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.education.entity.LessonSchedule;
import com.zeroone.star.education.mapper.ScheduleMapper;
import com.zeroone.star.education.service.ScheduleService;
import com.zeroone.star.project.dto.j5.schedule.ScheduleSaveDTO;
import com.zeroone.star.project.query.j5.schedule.SchedulePlanQuery;
import com.zeroone.star.project.vo.j5.schedule.SchedulePlanVO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class ScheduleServiceImpl extends ServiceImpl<ScheduleMapper, LessonSchedule> implements ScheduleService {
    @Autowired
    private ScheduleMapper scheduleMapper;

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

    @Override
    public ScheduleSaveDTO getById(Long id) {
        return null;
    }
}
