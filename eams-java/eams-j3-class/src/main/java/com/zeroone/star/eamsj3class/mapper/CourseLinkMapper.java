package com.zeroone.star.eamsj3class.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.eamsj3class.entity.CourseLink;

import com.zeroone.star.eamsj3class.entity.CourseLink;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

/**
 * <p>
 * 课程关联表 Mapper 接口
 * </p>
 *
 */
@Mapper
public interface CourseLinkMapper extends BaseMapper<CourseLink> {

    List<CourseLink> getCourseLinks(List<Long> courseIds);
}
