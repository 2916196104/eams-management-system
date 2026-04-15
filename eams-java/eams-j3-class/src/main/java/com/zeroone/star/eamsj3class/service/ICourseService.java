package com.zeroone.star.eamsj3class.service;

import com.zeroone.star.eamsj3class.entity.Course;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.j3.course.AddCourseDTO;
import com.zeroone.star.project.vo.JsonVO;

/**
 * <p>
 * 课程套餐表 服务类
 * </p>
 *
 * @author heavydrink
 * @since 2026-03-23
 */
public interface ICourseService extends IService<Course> {

    JsonVO<String> addCourse(AddCourseDTO addCourseDTO);
}
