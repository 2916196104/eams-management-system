package com.zeroone.star.eamsj3data.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.github.yulichang.query.MPJLambdaQueryWrapper;
import com.github.yulichang.wrapper.MPJLambdaWrapper;
import com.zeroone.star.eamsj3data.entity.Student;
import com.zeroone.star.eamsj3data.entity.StudentCourse;
import com.zeroone.star.eamsj3data.mapper.StudentCourseMapper;
import com.zeroone.star.eamsj3data.mapper.StudentMapper;
import com.zeroone.star.eamsj3data.service.StudentCourseService;
import com.zeroone.star.project.vo.j3.data.StudentLessonCountsVO;
import org.springframework.beans.factory.annotation.Autowired;

import java.time.LocalDateTime;
import java.util.List;

public class StudentCourseServiceImpl extends ServiceImpl<StudentCourseMapper, StudentCourse> implements StudentCourseService {
    @Autowired
    private StudentMapper studentMapper;

    @Override
    public List<StudentLessonCountsVO> getStudentLessonCounts(LocalDateTime beginTime, LocalDateTime endTime) {
        MPJLambdaWrapper<Student> wrapper = new MPJLambdaWrapper<>();

        wrapper.selectAs(Student::getId, StudentLessonCountsVO::getStudentId)
                .selectAs(Student::getName, StudentLessonCountsVO::getStudentName)
                .selectSum(StudentCourse::getCountLessonComplete, StudentLessonCountsVO::getLessonCount)
                .leftJoin(Student.class,Student::getId,StudentCourse::getStudentId)
                .groupBy(Student::getId)
                .orderByDesc(StudentLessonCountsVO::getLessonCount)
                .last("Limit 20");

        List<StudentLessonCountsVO> res =
                studentMapper.selectJoinList(StudentLessonCountsVO.class,wrapper);

        for(int i = 0;i < 20;i++){
            res.get(i).setStudentRank(i + 1);
        }
        return res;
    }
}
