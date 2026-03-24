package com.zeroone.star.student.mapper;

import com.zeroone.star.project.dto.j4.student.StudentQueryCondition;
import com.zeroone.star.project.vo.j4.student.StudentExportVO;
import com.zeroone.star.student.entity.Student;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

import java.util.List;

/**
 * <p>
 * 学生表 Mapper 接口
 * </p>
 *
 * @author gintoki
 * @since 2026-03-23
 */
@Mapper
public interface StudentMapper extends BaseMapper<Student> {
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


}
