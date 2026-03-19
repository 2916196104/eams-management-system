package com.homework.eamsj3class.service.impl;

import com.homework.eamsj3class.entity.Course;
import com.zeroone.star.project.dto.j3.course.CourseExportDTO;
import com.zeroone.star.project.dto.j3.course.CourseStatusDTO;
import org.mapstruct.Mapper;

import java.util.List;

/**
 * eamsj3class模块领域模型转换器
 * @authore Longan
 * @description
 */
@Mapper(componentModel = "spring")
public interface MsSampleMapper {
    CourseExportDTO courseToCEDTO(Course course);

    List<CourseExportDTO> coursesToCEDTOs(List<Course> courses);
}
