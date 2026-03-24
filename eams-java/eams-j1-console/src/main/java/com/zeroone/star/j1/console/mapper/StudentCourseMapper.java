package com.zeroone.star.j1.console.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j1.console.entity.StudentCourseDO;
import com.zeroone.star.project.dto.j1.enrollment.CourseEnrollmentDTO;
import com.zeroone.star.project.dto.j1.enrollment.MonthlyEnrollmentDTO;
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

    /**
     * 分页查询课程报名列表
     * @param page 分页参数
     * @param studentName 学员姓名
     * @param studentPhone 学员手机号
     * @param courseId 课程ID
     * @param classId 班级ID
     * @param status 报名状态
     * @param startDate 开始日期
     * @param endDate 结束日期
     * @return 分页结果
     */
    IPage<CourseEnrollmentDTO> selectCourseEnrollmentPage(
            Page<CourseEnrollmentDTO> page,
            @Param("studentName") String studentName,
            @Param("studentPhone") String studentPhone,
            @Param("courseId") Long courseId,
            @Param("classId") Long classId,
            @Param("status") Integer status,
            @Param("startDate") String startDate,
            @Param("endDate") String endDate
    );

    /**
     * 分页查询本月报名列表
     * @param page 分页参数
     * @param yearMonth 年月字符串
     * @param courseId 课程ID
     * @return 分页结果
     */
    IPage<MonthlyEnrollmentDTO> selectMonthlyEnrollmentPage(
            Page<MonthlyEnrollmentDTO> page,
            @Param("yearMonth") String yearMonth,
            @Param("courseId") Long courseId
    );
}
