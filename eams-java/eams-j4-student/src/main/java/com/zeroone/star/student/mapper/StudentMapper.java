package com.zeroone.star.student.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.student.entity.Student;
import com.zeroone.star.project.vo.j4.student.StudentExportExcelVO;
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