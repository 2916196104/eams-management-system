package com.zeroone.star.j5.courseschedule.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j5.courseschedule.entity.StudentLessonCountLog;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

/**
 * <p>
 * 描述：课次变更记录Mapper接口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
@Mapper
public interface StudentLessonCountLogMapper extends BaseMapper<StudentLessonCountLog> {

    /**
     * 分页查询学员课次变更流水
     * @param page 分页对象
     * @param studentId 学员ID
     * @param courseId 课程ID
     * @return 分页结果
     */
    @Select("<script>" +
            "SELECT l.*, c.name course_name, s.name student_name " +
            "FROM student_lesson_count_log l " +
            "LEFT JOIN course c ON l.course_id = c.id " +
            "LEFT JOIN student s ON l.student_id = s.id " +
            "WHERE l.id IS NOT NULL " +
            "<if test='studentId != null'>AND l.student_id = #{studentId}</if>" +
            "<if test='courseId != null'>AND l.course_id = #{courseId}</if>" +
            "ORDER BY l.add_time DESC" +
            "</script>")
    IPage<StudentLessonCountLog> selectLogPage(Page<StudentLessonCountLog> page,
                                                @Param("studentId") Long studentId,
                                                @Param("courseId") Long courseId);

    /**
     * 查询学员最新的课次变更记录
     * @param courseId 课程ID
     * @param studentId 学员ID
     * @return 最新记录
     */
    @Select("SELECT * FROM student_lesson_count_log " +
            "WHERE student_id = #{studentId} AND course_id = #{courseId} " +
            "ORDER BY add_time DESC LIMIT 1")
    StudentLessonCountLog selectLatestLog(@Param("courseId") Long courseId, @Param("studentId") Long studentId);
}
