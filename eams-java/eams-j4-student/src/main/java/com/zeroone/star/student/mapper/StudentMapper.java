package com.zeroone.star.student.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.student.entity.Student;
import org.apache.ibatis.annotations.Mapper;

/**
 * <p>
 * 描述：学员数据访问接口
 * </p>
 */
@Mapper
public interface StudentMapper extends BaseMapper<Student> {
}
