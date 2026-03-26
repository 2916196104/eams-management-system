package com.zeroone.star.j1.console.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.j1.console.entity.StudentDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

/**
 * <p>
 * 学员表 Mapper 接口
 * </p>
 * @author hxb
 */
@Mapper
public interface StudentMapper extends BaseMapper<StudentDO> {

    /**
     * 统计学员总数
     * @return 学员总数
     */
    @Select("SELECT COUNT(*) FROM student WHERE deleted = 0")
    Integer countTotalStudents();

    /**
     * 统计本月新增学员数
     * @param yearMonth 年月字符串，格式：yyyy-MM
     * @return 本月新增学员数
     */
    @Select("SELECT COUNT(*) FROM student WHERE deleted = 0 AND DATE_FORMAT(add_time, '%Y-%m') = #{yearMonth}")
    Integer countMonthNewStudents(@Param("yearMonth") String yearMonth);

    /**
     * 统计昨日新增学员数
     * @param yesterday 昨日日期，格式：yyyy-MM-dd
     * @return 昨日新增学员数
     */
    @Select("SELECT COUNT(*) FROM student WHERE deleted = 0 AND DATE(add_time) = #{yesterday}")
    Integer countYesterdayNewStudents(@Param("yesterday") String yesterday);
}
