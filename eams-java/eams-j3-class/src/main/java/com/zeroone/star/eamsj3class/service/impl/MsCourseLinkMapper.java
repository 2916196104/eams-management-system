package com.zeroone.star.eamsj3class.service.impl;


import com.zeroone.star.eamsj3class.entity.CourseLink;
import com.zeroone.star.project.dto.j3.course.CourseLinkDTO;
import org.mapstruct.Mapper;

/**
 * <p>
 * 描述：CourseLink模块领域模型转换器
 * </p>
 **/
@Mapper(componentModel="spring")
public interface MsCourseLinkMapper {


    /**
     * 描述：将CourseLink实体转换为CourseLinkDTO
     *
     * @param courseLink CourseLink实体
     * @return CourseLinkDTO
     */
    CourseLinkDTO toDTO(CourseLink courseLink);

    /**
     * 描述：将CourseLinkDTO转换为CourseLink实体
     *
     * @param courseLinkDTO CourseLinkDTO
     * @return CourseLink实体
     */
    CourseLink toEntity(CourseLinkDTO courseLinkDTO);




}
