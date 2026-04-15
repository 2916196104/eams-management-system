package com.zeroone.star.student.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.student.entity.StudentCourse;
import com.zeroone.star.student.mapper.StudentCourseMapper;
import com.zeroone.star.student.service.IStudentCourseService;
import org.springframework.stereotype.Service;

@Service
public class StudentCourseImpl extends ServiceImpl<StudentCourseMapper, StudentCourse> implements IStudentCourseService {
}
