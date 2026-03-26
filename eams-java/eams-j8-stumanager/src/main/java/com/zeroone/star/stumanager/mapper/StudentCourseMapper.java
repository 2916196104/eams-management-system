package com.zeroone.star.stumanager.mapper;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j8.stumanager.common.StudentCourseQuery;
import com.zeroone.star.project.vo.j8.stumanager.StudentCourseVO;
import com.zeroone.star.stumanager.entity.StudentCourse;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

/**
 * <p>
 * 报名签约表 Mapper 接口
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Mapper
public interface StudentCourseMapper extends BaseMapper<StudentCourse> {
    /**
     * 分页查询学员课程数据
     */
    Page<StudentCourseVO> getList(Page<StudentCourseVO> page, @Param("param") StudentCourseQuery param);
}
