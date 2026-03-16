package com.zeroone.star.project.j4.student;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.query.j4.student.CourseQuery;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j4.student.CourseCounterVO;
import com.zeroone.star.project.vo.j4.student.StudentScheduleVO;

import java.util.List;

public interface StudentApis {

    /**
     * 获取课程统计
     * @param studentQuery
     * @return 课程统计
     */
    JsonVO<PageDTO<CourseCounterVO>> getCourseCounter(StudentQuery studentQuery);

    /**
     * 获取课表
     * @param studentQuery
     * @return 课表
     */
    JsonVO<StudentScheduleVO> getStudentSchedule(StudentQuery studentQuery);
}