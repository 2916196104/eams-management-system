package com.zeroone.star.stumanager.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j8.stumanager.common.StudentCourseQuery;
import com.zeroone.star.project.vo.j8.stumanager.StudentCourseVO;
import com.zeroone.star.stumanager.entity.StudentCourse;
import com.baomidou.mybatisplus.extension.service.IService;

/**
 * <p>
 * 课程数据表 服务类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
public interface IStudentCourseService extends IService<StudentCourse> {
    /**
     * 按课程+学生姓名查询学员课程列表
     */
    PageDTO<StudentCourseVO> listStudentsByCourse(StudentCourseQuery condition);
}
