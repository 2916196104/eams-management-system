package com.zeroone.star.j5.courseschedule.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.j5.courseschedule.entity.StudentCourse;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Update;

/**
 * <p>
 * 描述：学员购课合同Mapper接口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
@Mapper
public interface StudentCourseMapper extends BaseMapper<StudentCourse> {

    /**
     * 扣减课次（上课签到后扣减已上课次）
     * @param id 学员购课合同ID
     * @param decCount 扣减数量
     * @return 影响行数
     */
    @Update("UPDATE student_course SET count_lesson_complete = count_lesson_complete + #{decCount} " +
            "WHERE id = #{id} AND (count_lesson_total - count_lesson_complete) >= #{decCount}")
    int decLessonCount(@Param("id") Long id, @Param("decCount") Integer decCount);

    /**
     * 回滚课次（撤销签到时恢复已上课次）
     * @param id 学员购课合同ID
     * @param count 恢复数量
     * @return 影响行数
     */
    @Update("UPDATE student_course SET count_lesson_complete = count_lesson_complete - #{count} " +
            "WHERE id = #{id} AND count_lesson_complete >= #{count}")
    int rollBackLessonCount(@Param("id") Long id, @Param("count") Integer count);

    /**
     * 批量扣减课次
     * @param ids 学员购课合同ID列表
     * @param decCount 扣减数量
     * @return 影响行数
     */
    @Update("<script>" +
            "UPDATE student_course SET count_lesson_complete = count_lesson_complete + #{decCount} " +
            "WHERE id IN " +
            "<foreach collection='ids' item='id' open='(' separator=',' close=')'>#{id}</foreach>" +
            "AND (count_lesson_total - count_lesson_complete) >= #{decCount}" +
            "</script>")
    int batchDecLessonCount(@Param("ids") Long[] ids, @Param("decCount") Integer decCount);

    /**
     * 批量回滚课次
     * @param ids 学员购课合同ID列表
     * @param count 恢复数量
     * @return 影响行数
     */
    @Update("<script>" +
            "UPDATE student_course SET count_lesson_complete = count_lesson_complete - #{count} " +
            "WHERE id IN " +
            "<foreach collection='ids' item='id' open='(' separator=',' close=')'>#{id}</foreach>" +
            "AND count_lesson_complete >= #{count}" +
            "</script>")
    int batchRollBackLessonCount(@Param("ids") Long[] ids, @Param("count") Integer count);
}
