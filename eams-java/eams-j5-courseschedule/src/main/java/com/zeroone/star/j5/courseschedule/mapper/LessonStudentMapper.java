package com.zeroone.star.j5.courseschedule.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j5.courseschedule.entity.LessonStudent;
import com.zeroone.star.project.query.PageQuery;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.time.LocalDateTime;
import java.util.List;

/**
 * <p>
 * 描述：课次学员关联Mapper接口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
@Mapper
public interface LessonStudentMapper extends BaseMapper<LessonStudent> {

    /**
     * 分页查询学员上课状态列表
     * @param page 分页对象
     * @param keyword 关键词（学员姓名/编号）
     * @param status 签到状态
     * @param query 分页参数
     * @return 分页结果
     */
    @Select("<script>" +
            "SELECT ls.*, l.title lesson_title, l.date lesson_date, l.start_time, l.end_time, " +
            "s.name student_name, s.mobile student_mobile, cls.name class_name " +
            "FROM lesson_student ls " +
            "LEFT JOIN lesson l ON ls.lesson_id = l.id " +
            "LEFT JOIN student s ON ls.student_id = s.id " +
            "LEFT JOIN `class` cls ON ls.class_id = cls.id " +
            "WHERE ls.id IS NOT NULL " +
            "<if test='keyword != null and keyword != \"\"'>AND (s.name LIKE CONCAT('%', #{keyword}, '%') OR s.mobile LIKE CONCAT('%', #{keyword}, '%'))</if>" +
            "<if test='status != null and status != \"\"'>AND ls.sign_state = #{status}</if>" +
            "ORDER BY l.date DESC, l.start_time DESC" +
            "</script>")
    IPage<LessonStudent> selectStudentStatusPage(Page<LessonStudent> page,
                                                   @Param("keyword") String keyword,
                                                   @Param("status") String status,
                                                   @Param("query") PageQuery query);

    /**
     * 签到更新
     * @param id 课次学员ID
     * @param signState 签到状态
     * @param signTime 签到时间
     * @param signType 签到方式
     * @return 影响行数
     */
    @Update("UPDATE lesson_student SET sign_state = #{signState}, sign_time = #{signTime}, sign_type = #{signType} WHERE id = #{id}")
    int updateSignState(@Param("id") Long id,
                        @Param("signState") Integer signState,
                        @Param("signTime") LocalDateTime signTime,
                        @Param("signType") Integer signType);

    /**
     * 批量更新签到状态
     * @param ids 课次学员ID列表
     * @param signState 签到状态
     * @param signTime 签到时间
     * @return 影响行数
     */
    @Update("<script>" +
            "UPDATE lesson_student SET sign_state = #{signState}, sign_time = #{signTime} " +
            "WHERE id IN " +
            "<foreach collection='ids' item='id' open='(' separator=',' close=')'>#{id}</foreach>" +
            "</script>")
    int batchUpdateSignState(@Param("ids") List<Long> ids,
                              @Param("signState") Integer signState,
                              @Param("signTime") LocalDateTime signTime);

    /**
     * 批量设置课程状态（停课/复课）- 修改课次表状态
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
     * 还原课程进度（清空签到状态）
     * @param ids 课次学员ID列表
     * @return 影响行数
     */
    @Update("<script>" +
            "UPDATE lesson_student SET sign_state = 0, sign_time = NULL, sign_type = NULL, " +
            "score = NULL, evaluation = NULL, evaluate_time = NULL, evaluate_teacher = NULL " +
            "WHERE id IN " +
            "<foreach collection='ids' item='id' open='(' separator=',' close=')'>#{id}</foreach>" +
            "</script>")
    int batchRestore(@Param("ids") List<Long> ids);
}
