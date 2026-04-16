package com.zeroone.star.stumanager.service;

import com.zeroone.star.stumanager.entity.ClassStudent;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.stumanager.entity.ClassStudent;

/**
 * <p>
 * 班级学员表 服务类
 * </p>
 */
public interface IClassStudentService extends IService<ClassStudent> {

    /**
     * 学生绑定班级
     * @param studentId 学生ID
     * @param classId 班级ID
     * @return 绑定结果
     */
    boolean bindStudentToClass(Long studentId, Long classId);

    /**
     * 学生解绑班级
     * @param studentId 学生ID
     * @return 解绑结果
     */
    boolean unbindStudentFromClass(Long studentId);

}
