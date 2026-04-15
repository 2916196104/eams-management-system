package com.zeroone.star.student.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.dto.j4.student.StudentEnrollDTO;
import com.zeroone.star.project.dto.j4.student.StudentQueryCondition;
import com.zeroone.star.project.vo.j4.student.StudentExportVO;
import com.zeroone.star.student.entity.Student;
import com.zeroone.star.project.vo.j4.student.StudentExportExcelVO;
import org.apache.ibatis.annotations.*;
import org.apache.ibatis.annotations.Update;

import java.util.List;

/**
 * <p>
 * 学生表 Mapper 接口
 * </p>
 *
 */
@Mapper
public interface StudentMapper extends BaseMapper<Student> {

    /**
     * 导出全部意向学员
     */
    @Select("SELECT " +
            "  s.id, " +
            "  s.name, " +
            "  u.mobile AS phone, " +
            "  CASE s.gender WHEN 1 THEN '男' WHEN 2 THEN '女' ELSE '未知' END AS gender, " +
            "  u.name AS parentName, " +
            "  CASE s.family_rel WHEN 1 THEN '爸爸' WHEN 2 THEN '妈妈' ELSE '其他' END AS familyRel, " +
            "  o.name AS schoolName, " +
            "  cg.name AS gradeName, " +
            "  st.name AS counselorName, " +
            "  DATE_FORMAT(s.birthday, '%Y-%m-%d') AS birthday " +
            "FROM student s " +
            "LEFT JOIN user u ON s.user_id = u.id " +
            "LEFT JOIN org o ON s.school_id = o.id " +
            "LEFT JOIN class_grade cg ON s.grade_id = cg.id " +
            "LEFT JOIN staff st ON s.counselor = st.id " +
            "WHERE s.stage = 0 AND s.deleted = 0")
    List<StudentExportExcelVO> selectIntentionStudentExportData();

    @Select("SELECT s.name, s.gender, s.idcard, DATE_FORMAT(s.graduation_date, '%Y-%m-%d') as graduationDate, " +
            "s.graduation_reason, u.name as parentName, u.mobile as parentMobile " +
            "FROM student s " +
            "LEFT JOIN user u ON s.user_id = u.id " +
            "WHERE s.deleted = 0 AND s.graduation_date IS NOT NULL " +
            "AND (s.name LIKE CONCAT('%', #{condition.name}, '%') OR #{condition.name} IS NULL) " +
            "AND (s.school_id = #{condition.schoolId} OR #{condition.schoolId} IS NULL) " +
            "AND (s.graduation_date >= #{condition.graduationDateStart} OR #{condition.graduationDateStart} IS NULL) " +
            "AND (s.graduation_date <= #{condition.graduationDateEnd} OR #{condition.graduationDateEnd} IS NULL)")
    List<StudentExportVO> selectGraduationStudentForExport(@Param("condition") StudentQueryCondition condition);



    /**
     * 导出在线学员
     */
    @Select("SELECT " +
            "  s.id, " +
            "  s.name, " +
            "  u.mobile AS phone, " +
            "  CASE s.gender WHEN 1 THEN '男' WHEN 2 THEN '女' ELSE '未知' END AS gender, " +
            "  u.name AS parentName, " +
            "  CASE s.family_rel WHEN 1 THEN '爸爸' WHEN 2 THEN '妈妈' ELSE '其他' END AS familyRel, " +
            "  o.name AS schoolName, " +
            "  cg.name AS gradeName, " +
            "  st.name AS counselorName, " +
            "  DATE_FORMAT(s.birthday, '%Y-%m-%d') AS birthday " +
            "FROM student s " +
            "LEFT JOIN user u ON s.user_id = u.id " +
            "LEFT JOIN org o ON s.school_id = o.id " +
            "LEFT JOIN class_grade cg ON s.grade_id = cg.id " +
            "LEFT JOIN staff st ON s.counselor = st.id " +
            "WHERE s.stage = 1 AND s.deleted = 0")
    List<StudentExportExcelVO> selectOnlineStudentExportData();

    /**
     * 修改学生阶段
     */
    @Update("UPDATE student SET stage = #{stage} WHERE id = #{id}")
    int updateStudentStage(StudentDTO studentDTO);

    @Insert("INSERT INTO student_course " +
            "(id, student_id, course_id, subject_id, start_date, expire_date, remark, " + // <--- 1. 这里加上 id
            "count_lesson_total, count_lesson_complete, amount, paid_amount, " +
            "operator, creator, add_time, verify_state, unit_price) " +
            "VALUES " +
            "(#{id}, #{studentId}, #{courseId}, #{subjectId}, #{startDate}, #{expireDate}, #{remark}, " + // <--- 2. 这里加上 #{id}
            "#{countLessonTotal}, 0, #{amount}, #{paidAmount}, " +
            "#{staffId}, #{staffId}, NOW(), 1, #{unitPrice})")
    int insertStudentCourse(StudentEnrollDTO enrollDTO);

    /**
     * 插入课时变更流水表 (student_lesson_count_log)
     */
    @Insert("INSERT INTO student_lesson_count_log " +
            "(id, student_id, course_id, change_count, remaining_count, staff_id, add_time, stage, remark) " +
            "VALUES " +
            "(#{id}, #{studentId}, #{courseId}, #{countLessonTotal}, #{countLessonTotal}, #{staffId}, NOW(), 1, '报名')")
    int insertEnrollLog(StudentEnrollDTO enrollDTO);


    /**
     * 查询学生详情
     */
    @Select("SELECT * FROM student WHERE id = #{id}")
    StudentDTO selectStudentDetail(Integer id);

    /**
     * 1. 保存学员 → 直接使用 BaseMapper 的 insert 方法，无需写SQL
     * 已自带：int insert(Student student);
     */

    /**
     * 2. 根据ID查询学员（给课次/课时汇总关联姓名用）
     */
    @Select("SELECT id, name FROM student WHERE id = #{studentId} AND deleted = 0")
    Student selectStudentNameById(Long studentId);

    /**
     * 3. 分页查询学员列表（给课时汇总关联姓名用）
     */
    @Select("<script>" +
            "SELECT id, name FROM student WHERE deleted = 0 " +
            "<if test='name != null and name != \"\"'>AND name LIKE CONCAT('%', #{name}, '%')</if>" +
            "</script>")
    List<Student> selectStudentList(String name);
}