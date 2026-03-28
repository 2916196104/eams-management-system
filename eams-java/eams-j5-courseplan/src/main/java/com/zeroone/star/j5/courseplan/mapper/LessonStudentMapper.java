package com.zeroone.star.j5.courseplan.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.j5.courseplan.entity.LessonStudent;
import org.apache.ibatis.annotations.Mapper;

/**
 * 课次学生关联 Mapper 接口
 */
@Mapper
public interface LessonStudentMapper extends BaseMapper<LessonStudent> {
}