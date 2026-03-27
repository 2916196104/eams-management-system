package com.zeroone.star.j5.classmanager.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.DO.j5.classmanager.ClassDO;
import com.zeroone.star.project.query.j5.classmanager.ClassPageQuery;
import com.zeroone.star.project.vo.j5.classmanager.ClassListVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface ClassMapper extends BaseMapper<ClassDO> {
    /**attachment
     * 分页查询班级列表（关联查询课程、教师、教室、年级名称）
     */
    IPage<ClassListVO> selectClassPage(@Param("page") Page<?> page, @Param("query") ClassPageQuery query);

    /**
     * 查询班级详情（根据ID）
     */
    @Select("SELECT " +
            "   c.id, c.name, c.course_id, c.classroom_id, c.teacher_id, c.grade_id, " +
            "   c.remark, c.be_over, c.over_time, c.start_date, c.end_date, " +
            "   c.planned_student_count, c.planned_lesson_count, c.school_id, c.org_id, " +
            "   c.add_time, c.edit_time, " +
            "   co.name AS course_name, " +
            "   s.name AS teacher_name, " +
            "   cr.name AS classroom_name, " +
            "   g.name AS grade_name " +
            "FROM class c " +
            "LEFT JOIN course co ON c.course_id = co.id AND co.deleted = 0 " +
            "LEFT JOIN staff s ON c.teacher_id = s.id AND s.deleted = 0 " +
            "LEFT JOIN classroom cr ON c.classroom_id = cr.id AND cr.deleted = 0 " +
            "LEFT JOIN class_grade g ON c.grade_id = g.id AND g.deleted = 0 " +
            "WHERE c.id = #{id} AND c.deleted = 0")
    ClassListVO selectClassDetail(@Param("id") Long id);

}
