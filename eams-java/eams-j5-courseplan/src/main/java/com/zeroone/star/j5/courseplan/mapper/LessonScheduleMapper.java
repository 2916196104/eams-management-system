package com.zeroone.star.j5.courseplan.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.j5.courseplan.entity.LessonSchedule;
import org.apache.ibatis.annotations.Mapper;

/**
 * 排课计划 Mapper 接口
 */
@Mapper
public interface LessonScheduleMapper extends BaseMapper<LessonSchedule> {
}