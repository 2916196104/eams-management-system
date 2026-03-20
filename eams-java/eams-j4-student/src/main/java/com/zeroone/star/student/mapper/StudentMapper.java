package com.zeroone.star.student.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.student.domain.po.Student;
import com.zeroone.star.student.domain.vo.StudentExportExcelVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

import java.util.List;

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
}