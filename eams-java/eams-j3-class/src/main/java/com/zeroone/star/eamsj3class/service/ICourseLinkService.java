package com.zeroone.star.eamsj3class.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.eamsj3class.entity.CourseLink;

import java.util.List;


/**
 * <p>
 * 课程关联表 服务类
 * </p>
 *
 * @author heavydrink
 * @since 2026-03-23
 */
public interface ICourseLinkService extends IService<CourseLink> {

    List<CourseLink> getCourseLinks(List<Long> courseIds);
}
