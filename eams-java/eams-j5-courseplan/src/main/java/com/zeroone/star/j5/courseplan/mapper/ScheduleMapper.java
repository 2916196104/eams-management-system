package com.zeroone.star.j5.courseplan.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;


import com.zeroone.star.j5.courseplan.entity.LessonSchedule;
import com.zeroone.star.project.query.j5.courseplan.SchedulePlanQuery;
import com.zeroone.star.project.vo.j5.courseplan.SchedulePlanVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

@Mapper
public interface ScheduleMapper extends BaseMapper<LessonSchedule> {


    /*
    * 排课计划 获取计划列表（条件+分页）
    * */
    Page<SchedulePlanVO> listAll(@Param("page") Page<SchedulePlanVO> page, @Param("query") SchedulePlanQuery query);
}
