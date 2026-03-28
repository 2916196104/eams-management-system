package com.zeroone.star.j5.courseplan.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.j5.courseplan.entity.ClassStudent;
import org.apache.ibatis.annotations.Mapper;

/**
 * 班级学生关联 Mapper 接口
 */
@Mapper
public interface ClassStudentMapper extends BaseMapper<ClassStudent> {
}