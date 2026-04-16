package com.zeroone.star.course.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.course.entity.CourseDO;
import com.zeroone.star.project.query.j9.course.CourseQuery;
import com.zeroone.star.project.vo.j9.course.CourseExportVO;
import com.zeroone.star.project.vo.j9.course.CourseListVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * <p>
 * 课程套餐表 Mapper 接口
 * </p>
 *
 * @author xxxcr
 * @since 2026-03-21
 */
@Mapper
public interface CourseMapper extends BaseMapper<CourseDO> {

    Page<CourseListVO> selectCourseList(Page<CourseListVO> page, @Param("query") CourseQuery query);

    List<CourseExportVO> selectCourseExportList(@Param("query") CourseQuery query);
}
