package com.zeroone.star.eamsj3class.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.eamsj3class.entity.CourseSection;
import com.zeroone.star.eamsj3class.service.CourseSectionService;
import com.zeroone.star.eamsj3class.mapper.CourseSectionMapper;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.CourseSectionDTO;
import com.zeroone.star.project.login.LoginApis;
import com.zeroone.star.project.query.CourseSectionPageQuery;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.List;
import java.util.stream.Collectors;

/**
* @author 22912
* @description 针对表【course_section(课程大纲)】的数据库操作Service实现
* @createDate 2026-03-23 20:45:39
*/
@Service
public class CourseSectionServiceImpl extends ServiceImpl<CourseSectionMapper, CourseSection>
    implements CourseSectionService{


    @Override
    public PageDTO<CourseSectionDTO> queryPage(CourseSectionPageQuery query) {
        // 1. 创建分页对象（告诉它页码和条数）
        Page<CourseSection> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // 2. 创建条件构造器
        LambdaQueryWrapper<CourseSection> wrapper = new LambdaQueryWrapper<>();

        // 3. 写查询条件
        wrapper.eq(CourseSection::getCourseId, query.getCourseId());           // 课程ID相等
        wrapper.like(query.getTitle() != null, CourseSection::getTitle, query.getTitle());  // 标题模糊
        wrapper.orderByAsc(CourseSection::getId);                              // 按ID排序

        // 3. 执行查询
        Page<CourseSection> pageResult = this.page(page, wrapper);

        // 4. 转换成 PageDTO
        return PageDTO.create(pageResult, CourseSectionDTO.class);
    }

    @Override
    public Long addSection(CourseSectionDTO dto) {
        CourseSection section = new CourseSection();
        BeanUtils.copyProperties(dto, section);
        section.setAddTime(LocalDateTime.now());
        section.setEditTime(LocalDateTime.now());
        section.setCreator(1L);  // TODO
        section.setEditor(1L);   // TODO
        section.setDeleted(0);

        this.save(section);
        return section.getId();
    }

    @Override
    public void deleteSection(Long id) {
        this.removeById(id);
    }

}




