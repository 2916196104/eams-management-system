package com.zeroone.star.course.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.course.entity.CourseSectionDO;
import org.apache.ibatis.annotations.Mapper;

/**
 * <p>
 * 描述：课程章节 Mapper 接口
 * </p>
 * @author YourName
 * @version 1.0.0
 */
@Mapper
public interface CourseChapterMapper extends BaseMapper<CourseSectionDO> {
}