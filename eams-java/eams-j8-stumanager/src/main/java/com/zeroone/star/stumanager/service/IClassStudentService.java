package com.zeroone.star.stumanager.service;

import com.zeroone.star.stumanager.entity.ClassStudent;
import com.baomidou.mybatisplus.extension.service.IService;

/**
 * <p>
 * 班级学员表 服务类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
public interface IClassStudentService extends IService<ClassStudent> {
    //判断学生id加入班级成功
    boolean bindStudentToClass(Long studentId, Long classId);
    ////判断学生id退出班级成功
    boolean unbindStudentFromClass(Long studentId);
}
