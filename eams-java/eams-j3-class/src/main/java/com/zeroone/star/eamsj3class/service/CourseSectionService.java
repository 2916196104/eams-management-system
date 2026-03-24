package com.zeroone.star.eamsj3class.service;

import com.zeroone.star.eamsj3class.entity.CourseSection;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.CourseSectionDTO;
import com.zeroone.star.project.query.CourseSectionPageQuery;

/**
* @author 殇昌
* @description 针对表【course_section】的数据库操作Service
* @createDate 2026-03-23 20:45:39
*/
public interface CourseSectionService extends IService<CourseSection> {
    PageDTO<CourseSectionDTO> queryPage(CourseSectionPageQuery query);
    Long addSection(CourseSectionDTO dto);
    void deleteSection(Long id);

}
