package com.zeroone.star.project.j5.schedule;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.schedule.ScheduleSaveDTO;
import com.zeroone.star.project.query.j5.schedule.SchedulePlanQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.schedule.LessonScheduleVO;
import com.zeroone.star.project.vo.j5.schedule.SchedulePlanVO;

import java.util.List;

/*
* 排课计划相关接口声明
* */
public interface SchedulePlanApis {
    /*
    * 描述：分页查询排课计划
    * */
    JsonVO<PageDTO<SchedulePlanVO>> queryPage(SchedulePlanQuery query);

    /*
    * 描述：新增或修改排课计划
    * */
    JsonVO<Long> saveSchedule(ScheduleSaveDTO scheduleSaveDTO);

    /*
    * 描述：删除排课计划(支持批量删除)
    * @return: 删除成功的id列表
    * */
    JsonVO<List<Long>> deleteSchedule(List<Long> ids);

    /*
    * 描述：根据id查询排课计划
    * */
    JsonVO<LessonScheduleVO> getScheduleById(Long id);
}
