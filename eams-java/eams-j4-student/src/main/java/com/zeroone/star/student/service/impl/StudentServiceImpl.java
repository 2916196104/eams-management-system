package com.zeroone.star.student.service.impl;

import com.zeroone.star.project.dto.j4.student.StudentDTO;
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

    /**
     * 学生报名课程
     * @param studentDTO
     * @return
     */
    @Transactional // 涉及多表操作，建议开启事务
    public boolean saveStudentCourse(StudentDTO studentDTO) {
        int courseCount = studentMapper.countCourseById(studentDTO.getCourseId());

        // 如果课程不存在，直接返回失败，不再往下走插入逻辑
        if (courseCount <= 0) {
            // 这里可以抛出自定义异常，或者直接返回 false
            return false;
        }

        int rows = studentMapper.insertStudentCourse(studentDTO);

        return rows > 0;
    }

    /**
     * 获取学员信息
     * @param studentQuery
     * @return
     */
    public StudentDTO getStudentDetail(StudentQuery studentQuery) {
        // 直接返回查询到的数据，不进行 Result 包装
        return studentMapper.selectStudentDetail(studentQuery);
    }
}
