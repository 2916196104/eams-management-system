package com.zeroone.star.j1.console.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.j1.console.entity.CourseDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

/**
 * <p>
 * 课程套餐表 Mapper 接口
 * </p>
 * @author hxb
 */
@Mapper
public interface CourseMapper extends BaseMapper<CourseDO> {

    /**
     * 统计课程总数
     * @return 课程总数
     */
    @Select("SELECT COUNT(*) FROM course WHERE deleted = 0")
    Integer countTotalCourses();

    /**
     * 根据ID获取课程名称
     * @param id 课程ID
     * @return 课程名称
     */
    @Select("SELECT name FROM course WHERE id = #{id} AND deleted = 0")
    String getNameById(Long id);
}
