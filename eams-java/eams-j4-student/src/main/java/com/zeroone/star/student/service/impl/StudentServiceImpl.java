package com.zeroone.star.student.service.impl;

import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.dto.j4.student.StudentEnrollDTO;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.student.mapper.StudentMapper;
import com.zeroone.star.student.service.StudentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

@Service
public class StudentServiceImpl implements StudentService {

    @Autowired
    private StudentMapper studentMapper;

    /**
     * 学员阶段设置
     * @param studentDTO
     * @return
     */
    public boolean updateStudentStage(StudentDTO studentDTO) {
        // 判断 Mapper 受影响行数是否大于 0
        return studentMapper.updateStudentStage(studentDTO) > 0;
    }

    @Transactional(rollbackFor = Exception.class) // 保证两个表同时成功
    public boolean saveStudentEnroll(StudentEnrollDTO enrollDTO) {

        // 1. 写入报名主表
        int count1 = studentMapper.insertStudentCourse(enrollDTO);

        // 2. 写入课时流水表
        int count2 = studentMapper.insertEnrollLog(enrollDTO);

        return count1 > 0 && count2 > 0;
    }


    /**
     * 获取学员信息
     * @param id
     * @return
     */
    public StudentDTO getStudentDetail(Integer id) {
        // 直接返回查询到的数据，不进行 Result 包装
        return studentMapper.selectStudentDetail(id);
    }
}
