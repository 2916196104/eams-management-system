package com.zeroone.star.j7.interaction.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j7.interaction.entity.Student;
import com.zeroone.star.j7.interaction.mapper.StudentMapper;
import com.zeroone.star.j7.interaction.service.StudentService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;

@Service
public class StudentServiceImpl extends ServiceImpl<StudentMapper, Student> implements StudentService {
    @Resource
    private StudentMapper studentMapper;

    // ===================== 新增：根据姓名查询学生列表 =====================

    /**
     * 1. 精确查询：姓名完全一致（比如查询叫"张三"的所有学生）
     * @param studentName 学生姓名
     * @return 学生列表
     */
    public List<Student> getStudentListByExactName(String studentName) {
        LambdaQueryWrapper<Student> wrapper = new LambdaQueryWrapper<>();
        // 精确匹配：name = ?
        wrapper.eq(Student::getName, studentName);
        // 查询符合条件的所有学生
        return studentMapper.selectList(wrapper);
    }
}
