package com.zeroone.star.j1.console.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.j1.console.entity.LessonStudentDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

/**
 * <p>
 * 课时学员关联表 Mapper 接口
 * </p>
 * @author hxb
 */
@Mapper
public interface LessonStudentMapper extends BaseMapper<LessonStudentDO> {

}
