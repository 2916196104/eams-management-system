package com.zeroone.star.eamsj3class.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.eamsj3class.entity.CourseLink;
import com.zeroone.star.eamsj3class.mapper.CourseLinkMapper;
import com.zeroone.star.eamsj3class.service.ICourseLinkService;
import org.springframework.stereotype.Service;

import java.util.Collections;
import java.util.List;


/**
 * <p>
 * 课程关联表 服务实现类
 * </p>
 *
 * @author heavydrink
 * @since 2026-03-23
 */
@Service
public class CourseLinkServiceImpl extends ServiceImpl<CourseLinkMapper, CourseLink> implements ICourseLinkService {

    @Override
    public List<CourseLink> getCourseLinks(List<Long> courseIds) {
        return this.baseMapper.getCourseLinks(courseIds);
    }
}
