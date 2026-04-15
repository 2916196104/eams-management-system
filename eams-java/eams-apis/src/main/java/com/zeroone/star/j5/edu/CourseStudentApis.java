package com.zeroone.star.j5.edu;

import com.zeroone.star.project.dto.j5.edu.CourseStudentDTO;
import com.zeroone.star.project.vo.JsonVO;

public interface CourseStudentApis {
    JsonVO<Long> saveCourseStudent(CourseStudentDTO courseStudentDTO);
}
