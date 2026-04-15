package com.zeroone.star.eamsj3class.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.eamsj3class.entity.CourseLink;
import com.zeroone.star.eamsj3class.mapper.CourseLinkMapper;
import com.zeroone.star.eamsj3class.service.ICourseLinkService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.CourseLinkDTO;
import com.zeroone.star.project.query.j3.course.CourseLinkQuery;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;


/**
 * <p>
 * 课程关联表 服务实现类
 * </p>
 *
 */
@Service
public class CourseLinkServiceImpl extends ServiceImpl<CourseLinkMapper, CourseLink> implements ICourseLinkService {
    @Resource
    MsCourseLinkMapper msCourseLinkMapper;

    @Override
    public PageDTO<CourseLinkDTO> listAll(CourseLinkQuery query) {
        //构建分页查询对象
        long pageIndex = (query == null || query.getPageIndex() <= 0) ? 1 : query.getPageIndex();
        long pageSize = (query == null || query.getPageSize() <= 0) ? 10 : query.getPageSize();
        Page<CourseLink> page = new Page<>(pageIndex, pageSize);
        //构建查询条件
        QueryWrapper<CourseLink> queryWrapper=new QueryWrapper<>();
        if (query != null) {
            queryWrapper.eq(query.getCourseId() != null, "course_id", query.getCourseId());
            queryWrapper.eq(query.getLinkedId() != null, "linked_id", query.getLinkedId());
        }
        //分页查询
        Page<CourseLink> result=baseMapper.selectPage(page,queryWrapper);
        return PageDTO.create(result,msCourseLinkMapper::toDTO);
    }

    @Override
    public Long add(CourseLinkDTO courseLinkDTO) {
        //参数校验
        if (courseLinkDTO == null || courseLinkDTO.getCourseId() == null || courseLinkDTO.getLinkedId() == null) {
            return 0L;
        }
        // 避免重复关联（course_id + linked_id）
        QueryWrapper<CourseLink> queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("course_id", courseLinkDTO.getCourseId());
        queryWrapper.eq("linked_id", courseLinkDTO.getLinkedId());
        if (baseMapper.selectCount(queryWrapper) > 0) {
            return 0L;
        }
        //构建实体
        CourseLink entity = msCourseLinkMapper.toEntity(courseLinkDTO);
        //添加
        if (courseLinkDTO.getId() != null) {
            entity.setId(courseLinkDTO.getId());
        }

        return baseMapper.insert(entity) > 0 ? 1L : 0L;
    }

    @Override
    public List<Long> delete(List<Long> ids) {
        //参数校验
        if (ids == null || ids.isEmpty()) {
            return Collections.emptyList();
        }

        // 先查出真实存在的记录，返回真正删除成功的 id
        List<CourseLink> existing = baseMapper.selectBatchIds(ids);
        if (existing == null || existing.isEmpty()) {
            return Collections.emptyList();
        }
        //组装返回值
        List<Long> existingIds = existing.stream()
                .map(CourseLink::getId)
                .collect(Collectors.toList());
        //删除
        int affected = baseMapper.deleteBatchIds(existingIds);
        return affected > 0 ? existingIds : Collections.emptyList();
    }
    @Override
    public List<CourseLink> getCourseLinks(List<Long> courseIds) {
        return this.baseMapper.getCourseLinks(courseIds);
    }
}
