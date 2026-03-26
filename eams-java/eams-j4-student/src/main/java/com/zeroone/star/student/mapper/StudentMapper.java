package com.zeroone.star.student.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.j4.student.StudentQueryCondition;
import com.zeroone.star.project.vo.j4.student.StudentExportVO;
import com.zeroone.star.student.entity.Student;
import com.zeroone.star.project.vo.j4.student.StudentExportExcelVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

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
}