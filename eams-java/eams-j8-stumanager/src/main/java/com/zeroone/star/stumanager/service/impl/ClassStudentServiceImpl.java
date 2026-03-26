package com.zeroone.star.stumanager.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.stumanager.entity.ClassStudent;
import com.zeroone.star.stumanager.mapper.ClassStudentMapper;
import com.zeroone.star.stumanager.service.IClassStudentService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;

/**
 * 班级学员表 服务实现类
 */
@Service
public class ClassStudentServiceImpl extends ServiceImpl<ClassStudentMapper, ClassStudent> implements IClassStudentService {

    /**
     * 实现接口中定义的 bindStudentToClass 方法
     * @param studentId 学生ID
     * @param classId 班级ID
     * @return 是否绑定成功
     */
    @Override
    public boolean bindStudentToClass(Long studentId, Long classId) {
        // 直接复用 MyBatis-Plus 的 save 方法，插入学生-班级关联记录
        ClassStudent classStudent = new ClassStudent();
        classStudent.setStudentId(studentId);
        classStudent.setClassId(classId);
        return this.save(classStudent);
    }

    /**
     * 实现接口中定义的 unbindStudentFromClass 方法
     * @param studentId 学生ID
     * @return 是否解绑成功
     */
    @Override
    public boolean unbindStudentFromClass(Long studentId) {
        // 构建查询条件：删除该学生的所有班级关联记录
        QueryWrapper<ClassStudent> wrapper = new QueryWrapper<>();
        wrapper.eq("student_id", studentId);
        // 复用 MyBatis-Plus 的 remove 方法
        return this.remove(wrapper);
    }
}
