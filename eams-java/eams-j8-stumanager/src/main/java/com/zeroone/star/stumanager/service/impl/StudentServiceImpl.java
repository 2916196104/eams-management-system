package com.zeroone.star.stumanager.service.impl;

import com.zeroone.star.stumanager.entity.Student;
import com.zeroone.star.stumanager.mapper.StudentMapper;
import com.zeroone.star.stumanager.service.IStudentService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;

/**
 * <p>
 * 学生表 服务实现类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Service
public class StudentServiceImpl extends ServiceImpl<StudentMapper, Student> implements IStudentService {

}
