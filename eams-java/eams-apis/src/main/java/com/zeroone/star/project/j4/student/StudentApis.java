package com.zeroone.star.project.j4.student;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.ResponseDTO;

import com.zeroone.star.project.query.j4.student.CourseQuery;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;

public interface StudentApis {

    JsonVO<PageDTO<ResponseDTO>> queryCourseStudent(CourseQuery condition);

    JsonVO<PageDTO<ResponseDTO>> listAllStudent(StudentQuery condition);

}
