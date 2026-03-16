package com.zeroone.star.education.service;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.education.entity.LessonSchedule;
import com.zeroone.star.project.dto.j5.schedule.ScheduleSaveDTO;
import com.zeroone.star.project.query.j5.schedule.SchedulePlanQuery;
import com.zeroone.star.project.vo.j5.schedule.SchedulePlanVO;

/*
* 描述：排课计划服务接口
* */
public interface ScheduleService extends IService<LessonSchedule> {
    /*
    * 分页查询排课计划
    * */
    Page<SchedulePlanVO> listAll(SchedulePlanQuery query);

    /*
    * 根据id查询排课计划详情
    * */
    ScheduleSaveDTO getById(Long id);
}
