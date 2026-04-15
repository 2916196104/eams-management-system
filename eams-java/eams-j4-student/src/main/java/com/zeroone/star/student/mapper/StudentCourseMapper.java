package com.zeroone.star.student.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.j4.student.StudentDetailVO;
import com.zeroone.star.student.entity.StudentCourse;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

import java.util.List;

/**
 * <p>
 * 描述：学员签约记录数据访问接口
 * </p>
 */
@Mapper
public interface StudentCourseMapper extends BaseMapper<StudentCourse> {

    /**
     * 1. 获取学员课次数据（按学员ID查询）
     * 查询【组长提供的完整StudentCourse字段】
     */
    @Select({
            "<script>",
            "SELECT ",
            "sc.*, ",
            "s.name, ",
            "c.name AS courseName ",  // 👈 这里加上课程名
            "FROM student_course sc ",
            "LEFT JOIN student s ON sc.student_id = s.id ",
            "LEFT JOIN course c ON sc.course_id = c.id ",  // 👈 关联课程表
            "WHERE sc.deleted = 0 ",
            "AND sc.student_id = #{studentId} ",
            "</script>"
    })
    List<StudentCourse> listCourseTimesByStudentId(@Param("studentId") Long studentId);

    /**
     * 2. 获取课时汇总列表（条件+分页）
     * 支持：学员ID、姓名、手机号查询 + 完整课次字段返回
     */
    @Select({
            "<script>",
            "SELECT ",
            "sc.*, ",
            "s.name, ",  // 只保留学员姓名
            "sc.count_lesson_total AS lessonCount, ",
            "sc.count_lesson_complete AS decLessonCount ",
            "FROM student_course sc ",
            "LEFT JOIN student s ON sc.student_id = s.id ",
            "WHERE sc.deleted = 0 ",
            "<if test=\"query.courseId != null\">",
            "   AND sc.course_id = #{query.courseId} ",
            "</if>",
            "</script>"
    })
    Page<StudentCourse> getLessonSummaryPage(Page<StudentCourse> page, @Param("query") StudentQuery query);
}