package com.zeroone.star.project.student;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j8.StudentCourseQuery;
import com.zeroone.star.project.query.j8.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentCourseVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentVO;


/**
 * 学生模块 API 定义
 */
public interface StudentApis {

    /**
     * 分页 + 条件 查询学员列表
     */
    JsonVO<PageDTO<StudentVO>> queryStudents(StudentQuery query);
    /**
     * 【开通指定课程的学员列表（含课次）】分页查询
     */
    JsonVO<PageDTO<StudentCourseVO>> queryStudentsByCourse(StudentCourseQuery condition);
}
