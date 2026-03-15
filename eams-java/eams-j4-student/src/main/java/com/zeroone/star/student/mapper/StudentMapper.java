package com.zeroone.star.student.mapper;

import com.zeroone.star.student.entity.Student;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;

/**
 * <p>
 * 学生表 Mapper 接口
 * </p>
 *
 * @author erji
 * @since 2026-03-15
 */
@Mapper
public interface StudentMapper extends BaseMapper<Student> {

}
