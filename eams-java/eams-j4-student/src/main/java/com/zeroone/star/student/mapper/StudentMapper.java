package com.zeroone.star.student.mapper;

import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

@Mapper
public interface StudentMapper {

    /**
     * 修改学生阶段
     */
    @Update("UPDATE student SET stage = #{stage} WHERE id = #{id}")
    int updateStudentStage(StudentDTO studentDTO);

    /**
     * 查询课程是否存在
     */
    @Select("SELECT COUNT(*) FROM course WHERE id = #{courseId}")
    int countCourseById(Long courseId);

    /**
     * 学员报名插入
     */
    @Insert("INSERT INTO student_course (student_id, course_id) VALUES (#{id}, #{courseId})")
    int insertStudentCourse(StudentDTO studentDTO);


    /**
     * 查询学生详情
     */
    @Select("SELECT * FROM student WHERE id = #{id}")
    StudentDTO selectStudentDetail(StudentQuery studentQuery);
}
