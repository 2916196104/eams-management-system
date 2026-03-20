package com.zeroone.star.j5.courseschedule.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j5.courseschedule.entity.LessonStudent;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Map;

@Mapper
public interface LessonStudentMapper extends BaseMapper<LessonStudent> {

    @Select("SELECT * FROM lesson_student WHERE lesson_id = #{lessonId} AND student_id = #{studentId} LIMIT 1")
    LessonStudent selectByLessonAndStudent(@Param("lessonId") Long lessonId, @Param("studentId") Long studentId);

    @Select("<script>" +
            "SELECT ls.*, l.title lesson_title, l.date lesson_date, l.start_time, l.end_time, " +
            "s.name student_name, s.mobile student_mobile, cls.name class_name " +
            "FROM lesson_student ls " +
            "LEFT JOIN lesson l ON ls.lesson_id = l.id " +
            "LEFT JOIN student s ON ls.student_id = s.id " +
            "LEFT JOIN `class` cls ON ls.class_id = cls.id " +
            "WHERE ls.id IS NOT NULL " +
            "<if test='keyword != null and keyword != \"\"'>AND (s.name LIKE CONCAT('%', #{keyword}, '%') OR s.mobile LIKE CONCAT('%', #{keyword}, '%'))</if>" +
            "<if test='status != null and status != \"\"'>AND ls.sign_state = #{status}</if>" +
            "ORDER BY l.date DESC, l.start_time DESC" +
            "</script>")
    IPage<Map<String, Object>> selectStudentStatusPage(Page<Map<String, Object>> page,
                                                        @Param("keyword") String keyword,
                                                        @Param("status") String status);

    @Update("UPDATE lesson_student SET sign_state = #{signState}, sign_time = #{signTime}, sign_type = #{signType} WHERE id = #{id}")
    int updateSignState(@Param("id") Long id,
                        @Param("signState") Integer signState,
                        @Param("signTime") LocalDateTime signTime,
                        @Param("signType") Integer signType);

    @Update("<script>" +
            "UPDATE lesson_student SET sign_state = #{signState}, sign_time = #{signTime} " +
            "WHERE id IN " +
            "<foreach collection='ids' item='id' open='(' separator=',' close=')'>#{id}</foreach>" +
            "</script>")
    int batchUpdateSignState(@Param("ids") List<Long> ids,
                             @Param("signState") Integer signState,
                             @Param("signTime") LocalDateTime signTime);

    @Update("<script>" +
            "UPDATE lesson_student SET sign_state = 0, sign_time = NULL, sign_type = NULL, " +
            "score = NULL, evaluation = NULL, evaluate_time = NULL, evaluate_teacher = NULL " +
            "WHERE id IN " +
            "<foreach collection='ids' item='id' open='(' separator=',' close=')'>#{id}</foreach>" +
            "</script>")
    int batchRestore(@Param("ids") List<Long> ids);
}