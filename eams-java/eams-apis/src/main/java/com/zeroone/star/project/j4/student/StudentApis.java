package com.zeroone.star.project.j4.student;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.query.j4.student.CourseQuery;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;

public interface StudentApis {

    /**
     * 分页查询指定课程的学生
     * @param condition 查询条件
     * @return 学生信息
     */
    JsonVO<PageDTO<StudentDTO>> queryCourseStudent(CourseQuery condition);

    /**
     * 分页查询学生列表
     * @param condition 查询条件
     * @return 学生信息
     */
    JsonVO<PageDTO<StudentDTO>> listAllStudent(StudentQuery condition);

}
