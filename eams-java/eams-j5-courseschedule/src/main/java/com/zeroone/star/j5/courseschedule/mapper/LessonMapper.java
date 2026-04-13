package com.zeroone.star.j5.courseschedule.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j5.courseschedule.entity.Lesson;
import com.zeroone.star.project.DO.j5.courseschedule.LessonDo;
import com.zeroone.star.project.dto.j5.courseschedule.LessonParamDTO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.util.List;

/**
 * <p>
 * 描述：课次Mapper接口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
@Mapper
public interface LessonMapper extends BaseMapper<Lesson> {

    /**
     * 批量设置课次状态（停课/复课）
     * @param lessonIds 课次ID列表
     * @param state 状态值（0-已停课，1-进行中）
     * @return 影响行数
     */
    @Update("<script>" +
            "UPDATE lesson SET state = #{state} " +
            "WHERE id IN " +
            "<foreach collection='lessonIds' item='id' open='(' separator=',' close=')'>#{id}</foreach>" +
            "</script>")
    int batchToggleStatus(@Param("lessonIds") List<Long> lessonIds, @Param("state") Integer state);

    /**
     * 条件+分页列表查询
     * @param page 分页对象
     * @param param 查询参数
     * @return 分页结果
     */
    @Select("<script>" +
            "SELECT l.* FROM lesson l " +
            "LEFT JOIN course c ON l.course_id = c.id " +
            "LEFT JOIN `class` cls ON l.class_id = cls.id " +
            "WHERE l.deleted = 0 " +
            "<if test='param.onTrial != null'>AND l.on_trial = #{param.onTrial}</if>" +
            "<if test='param.courseIds != null and param.courseIds.size() > 0'>AND l.course_id IN " +
            "<foreach collection='param.courseIds' item='id' open='(' separator=',' close=')'>#{id}</foreach></if>" +
            "<if test='param.classIds != null and param.classIds.size() > 0'>AND l.class_id IN " +
            "<foreach collection='param.classIds' item='id' open='(' separator=',' close=')'>#{id}</foreach></if>" +
            "<if test='param.teacherIds != null and param.teacherIds.size() > 0'>AND l.teacher_id IN " +
            "<foreach collection='param.teacherIds' item='id' open='(' separator=',' close=')'>#{id}</foreach></if>" +
            "<if test='param.studentIds != null and param.studentIds.size() > 0'>AND EXISTS (" +
            "SELECT 1 FROM lesson_student ls WHERE ls.lesson_id = l.id AND ls.student_id IN " +
            "<foreach collection='param.studentIds' item='id' open='(' separator=',' close=')'>#{id}</foreach>" +
            ")</if>" +
            "<if test='param.subjectId != null'>AND c.subject_id = #{param.subjectId}</if>" +
            "<if test='param.roomId != null'>AND l.room_id = #{param.roomId}</if>" +
            "<if test='param.startDate != null'>AND l.date &gt;= #{param.startDate}</if>" +
            "<if test='param.endDate != null'>AND l.date &lt;= #{param.endDate}</if>" +
            "ORDER BY l.date DESC, l.start_time DESC" +
            "</script>")
    IPage<Lesson> selectLessonPage(Page<Lesson> page, @Param("param") LessonParamDTO param);
}
