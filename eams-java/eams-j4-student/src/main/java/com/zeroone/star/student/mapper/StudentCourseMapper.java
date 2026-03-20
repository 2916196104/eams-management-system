package com.zeroone.star.student.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.student.entity.StudentCourse;
import org.apache.ibatis.annotations.Mapper;

/**
 * <p>
 * 描述：学员签约记录数据访问接口
 * </p>
 */
@Mapper
public interface StudentCourseMapper extends BaseMapper<StudentCourse> {
}
