package com.zeroone.star.j7.interaction.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.j7.interaction.entity.Student;

import java.util.List;

public interface StudentService extends IService<Student> {
    List<Student> getStudentListByExactName(String studentName);
}
