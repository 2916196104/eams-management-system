package com.zeroone.star.j1.console.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.j1.console.entity.StudentCourseDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

import java.util.List;
import java.util.Map;

/**
 * <p>
 * 报名签约表 Mapper 接口
 * </p>
 * @author hxb
 */
@Mapper
public interface StudentCourseMapper extends BaseMapper<StudentCourseDO> {

    /**
     * 统计本月报名数
     * @param yearMonth 年月字符串，格式：yyyy-MM
     * @return 本月报名数
     */
    @Select("SELECT COUNT(*) FROM student_course WHERE deleted = 0 AND DATE_FORMAT(add_time, '%Y-%m') = #{yearMonth}")
    Integer countMonthEnrollments(@Param("yearMonth") String yearMonth);

    /**
     * 统计本月报名金额
     * @param yearMonth 年月字符串，格式：yyyy-MM
     * @return 本月报名金额（元）
     */
    @Select("SELECT COALESCE(SUM(amount), 0) FROM student_course WHERE deleted = 0 AND DATE_FORMAT(add_time, '%Y-%m') = #{yearMonth}")
    Double countMonthEnrollmentAmount(@Param("yearMonth") String yearMonth);

    /**
     * 统计每日报名数
     * @param yearMonth 年月字符串，格式：yyyy-MM
     * @return 每日报名数据列表
     */
    @Select("SELECT DATE_FORMAT(add_time, '%Y-%m-%d') as date, COUNT(*) as count " +
            "FROM student_course " +
            "WHERE deleted = 0 AND DATE_FORMAT(add_time, '%Y-%m') = #{yearMonth} " +
            "GROUP BY DATE_FORMAT(add_time, '%Y-%m-%d') " +
            "ORDER BY date")
    List<Map<String, Object>> countDailyEnrollments(@Param("yearMonth") String yearMonth);

    /**
     * 查询课程报名金额排行
     * @param limit 限制条数
     * @return 课程报名金额排行
     */
    @Select("SELECT c.name as courseName, SUM(sc.amount) as amount " +
            "FROM student_course sc " +
            "LEFT JOIN course c ON sc.course_id = c.id " +
            "WHERE sc.deleted = 0 AND c.deleted = 0 " +
            "GROUP BY sc.course_id, c.name " +
            "ORDER BY amount DESC " +
            "LIMIT #{limit}")
    List<Map<String, Object>> selectCourseEnrollmentAmountRank(@Param("limit") Integer limit);


}
