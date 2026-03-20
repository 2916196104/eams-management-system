package com.zeroone.star.student.mapper;

import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.dto.j4.student.StudentEnrollDTO;
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
     * 插入报名表 (student_course)
     */
    @Insert("INSERT INTO student_course " +
            "(student_id, course_id, subject_id, start_date, expire_date, remark, " +
            "count_lesson_total, count_lesson_complete, amount, paid_amount, " +
            "operator, creator, add_time, verify_state, unit_price) " +
            "VALUES " +
            "(#{studentId}, #{courseId}, #{subjectId}, #{startDate}, #{expireDate}, #{remark}, " +
            "#{countLessonTotal}, 0, #{amount}, #{paidAmount}, " +
            "#{staffId}, #{staffId}, NOW(), 1, #{unitPrice})")
    int insertStudentCourse(StudentEnrollDTO enrollDTO);

    /**
     * 插入课时变更流水表 (student_lesson_count_log)
     */
    @Insert("INSERT INTO student_lesson_count_log " +
            "(student_id, course_id, change_count, remaining_count, staff_id, add_time, stage, remark) " +
            "VALUES " +
            "(#{studentId}, #{courseId}, #{countLessonTotal}, #{countLessonTotal}, #{staffId}, NOW(), 1, '报名')")
    int insertEnrollLog(StudentEnrollDTO enrollDTO);


    /**
     * 查询学生详情
     */
    @Select("SELECT * FROM student WHERE id = #{id}")
    StudentDTO selectStudentDetail(Integer id);
}
