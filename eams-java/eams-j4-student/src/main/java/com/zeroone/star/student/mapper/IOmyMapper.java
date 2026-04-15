package com.zeroone.star.student.mapper;

import com.zeroone.star.student.entity.StudentLessonCountLog;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Result;
import org.apache.ibatis.annotations.Results;
import org.apache.ibatis.annotations.Select;

import java.util.List;

@Mapper
public interface IOmyMapper {

    @Results(id = "studentLessonCountLog", value = {
            @Result(column = "course_id", property = "courseId"),
            @Result(column = "change_count", property = "changeCount"),
            @Result(column = "add_time", property = "addTime"),
            @Result(column = "staff_id", property = "staffId"),
            @Result(column = "remark", property = "remark"),
            @Result(column = "remaining_count", property = "remainingCount"),
    })
    @Select("SELECT course_id,change_count," +
            "add_time,staff_id,remark,remaining_count" +
            " FROM student_lesson_count_log " +
            "WHERE student_id = #{studentId} " +
            "ORDER BY add_time ASC")
    List<StudentLessonCountLog> getById(int StudentID);

    @Select("select name from student where id = ${StudentID}")
    String SelectNameById( String StudentID);

    @Select("select name from course where subject_id = ${courseId}")
    String SelectCourseById(int courseId);

    @Select("select name from staff where id = ${staffId}")
    String SelectStaffById(int staffId);
}
