package com.zeroone.star.eamsj3class.service.impl;

import com.zeroone.star.eamsj3class.entity.Subject;
import com.zeroone.star.project.dto.j3.course.CourseExportDTO;
import com.zeroone.star.project.dto.j3.course.SubjectDTO;
import org.mapstruct.Mapper;

import java.util.List;

/**
 * eamsj3class模块领域模型转换器
 * @authore Longan
 * @description
 */
@Mapper(componentModel = "spring")
public interface MsSampleMapper {
    CourseExportDTO courseToCEDTO(CourseExportDTO course);

    List<CourseExportDTO> coursesToCEDTOs(List<CourseExportDTO> courses);

    SubjectDTO subjectToDto(Subject entity);

    Subject subjectDtoToDo(SubjectDTO dto);

}
