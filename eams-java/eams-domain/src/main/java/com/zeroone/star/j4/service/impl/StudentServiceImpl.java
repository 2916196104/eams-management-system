package com.zeroone.star.j4.service.impl;

import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j4.entity.Student;
import com.zeroone.star.j4.mapper.StudentMapper;
import com.zeroone.star.j4.service.IStudentService;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;

@Service
public class StudentServiceImpl extends ServiceImpl<StudentMapper, Student> implements IStudentService {

    @Override
    public boolean updateHeadImg(Long studentId, String headImgUrl) {
        // 创建更新条件
        LambdaUpdateWrapper<Student> wrapper = new LambdaUpdateWrapper<>();
        // 设置条件：id = studentId
        wrapper.eq(Student::getId, studentId);
        // 设置要更新的字段：head_img = headImgUrl
        wrapper.set(Student::getHeadImg, headImgUrl);
        // 执行更新
        return this.update(wrapper);
    }

    @Override
    public StudentDTO getStudentById(Long studentId) {
        Student student = this.getById(studentId);
        if (student == null) {
            return null;
        }
        StudentDTO dto = new StudentDTO();
        BeanUtils.copyProperties(student, dto);
        return dto;
    }
}
