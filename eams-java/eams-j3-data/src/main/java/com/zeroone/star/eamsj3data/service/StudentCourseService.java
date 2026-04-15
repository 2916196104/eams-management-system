package com.zeroone.star.eamsj3data.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.eamsj3data.entity.StudentCourse;
import com.zeroone.star.project.vo.j3.data.StudentLessonCountsVO;

import java.time.LocalDateTime;
import java.util.List;

public interface StudentCourseService extends IService<StudentCourse> {
    List<StudentLessonCountsVO> getStudentLessonCounts(LocalDateTime beginTime, LocalDateTime endTime);
}
