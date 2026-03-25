package com.zeroone.star.student.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j4.student.ClassQuery;
import com.zeroone.star.project.vo.j4.student.ClassDetailVO;
import com.zeroone.star.student.entity.ClassDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface ClassMapper extends BaseMapper<ClassDO> {

    @Select("<script>" +
            "SELECT c.id, c.name, c.course_id, c.classroom_id, c.planned_student_count, " +
            "       cr.name AS classroom_name, " +
            "       co.name AS subject, " +
            "       COUNT(cs.id) AS student_count " +
            "FROM class c " +
            "LEFT JOIN course co ON c.course_id = co.id AND co.deleted = 0 " +
            "LEFT JOIN classroom cr ON c.classroom_id = cr.id AND cr.deleted = 0 " +
            "LEFT JOIN class_student cs ON c.id = cs.class_id AND cs.deleted = 0 " +
            "WHERE c.deleted = 0 " +
            "<if test='condition.name != null and condition.name != \"\"'>" +
            "  AND c.name LIKE CONCAT('%', #{condition.name}, '%') " +
            "</if>" +
            "GROUP BY c.id, c.name, c.course_id, c.classroom_id, c.planned_student_count, " +
            "         cr.name, co.name " +
            "</script>")
    IPage<ClassDetailVO> selectClassPage(Page<?> page, @Param("condition") ClassQuery condition);
}