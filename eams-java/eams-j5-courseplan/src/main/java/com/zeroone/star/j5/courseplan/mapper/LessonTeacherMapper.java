package com.zeroone.star.j5.courseplan.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.j5.courseplan.entity.LessonTeacher;
import org.apache.ibatis.annotations.Mapper;

/**
 * 课次教师关联 Mapper 接口
 */
@Mapper
public interface LessonTeacherMapper extends BaseMapper<LessonTeacher> {
}