package com.zeroone.star.student.service.impl;

import com.zeroone.star.student.entity.Student;
import com.zeroone.star.student.mapper.StudentMapper;
import com.zeroone.star.student.service.IStudentService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;

/**
 * <p>
 * 学生表 服务实现类
 * </p>
 *
 * @author erji
 * @since 2026-03-15
 */
@Service
public class StudentServiceImpl extends ServiceImpl<StudentMapper, Student> implements IStudentService {

}
