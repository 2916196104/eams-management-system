package com.zeroone.star.stumanager.mapper;

import com.zeroone.star.project.vo.j8.stumanager.StudentVO;
import com.zeroone.star.stumanager.entity.Student;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

/**
 * <p>
 * 学生表 Mapper 接口
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Mapper
public interface StudentMapper extends BaseMapper<Student> {

    StudentVO getStudentDetailsById(@Param("id") Long id);
}
