package com.zeroone.star.course.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.course.entity.CourseLinkDO;
import com.zeroone.star.course.entity.CourseDO;
import com.zeroone.star.course.entity.SubjectDO;
import com.zeroone.star.course.mapper.CourseLinkMapper;
import com.zeroone.star.course.mapper.CourseMapper;
import com.zeroone.star.course.mapper.SubjectMapper;
import com.zeroone.star.course.service.IRelatedCourseService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.course.CourseLinkDTO;
import com.zeroone.star.project.query.j9.course.CourseLinkPageQuery;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

/**
 * 关联课程服务实现
 */
@Slf4j
@Service
public class RelatedCourseServiceImpl extends ServiceImpl<CourseLinkMapper, CourseLinkDO> implements IRelatedCourseService {

    @Resource
    private CourseLinkMapper courseLinkMapper;

    @Resource
    private CourseMapper courseMapper;

    @Resource
    private SubjectMapper subjectMapper;

    @Override
    public PageDTO<CourseLinkDTO> listPage(CourseLinkPageQuery condition) {
        // 检查课程ID是否存在
        if (condition.getCourseId() != null) {
            CourseDO course = courseMapper.selectById(condition.getCourseId());
            if (course == null) {
                throw new IllegalArgumentException("课程不存在，ID: " + condition.getCourseId());
            }
        }
        
        Page<CourseLinkDO> page = new Page<>(condition.getPageIndex(), condition.getPageSize());
        LambdaQueryWrapper<CourseLinkDO> wrapper = new LambdaQueryWrapper<>();
        
        // 构建查询条件
        if (condition.getCourseId() != null) {
            wrapper.eq(CourseLinkDO::getCourseId, condition.getCourseId());
        }
        if (condition.getLinkedId() != null) {
            wrapper.eq(CourseLinkDO::getLinkedId, condition.getLinkedId());
        }
        
        // 执行分页查询
        page = courseLinkMapper.selectPage(page, wrapper);
        
        // 转换为 DTO 并过滤课程名称
        List<CourseLinkDTO> rows = page.getRecords().stream()
                .map(link -> {
                    CourseLinkDTO dto = new CourseLinkDTO();
                    
                    // 查询关联课程信息
                    CourseDO course = courseMapper.selectById(link.getLinkedId());
                    if (course != null) {
                        dto.setName(course.getName());
                        dto.setPrice(course.getPrice());
                        dto.setUnitName(course.getUnitName());

                        // 查询科目信息
                        SubjectDO subject = subjectMapper.selectById(course.getSubjectId());
                        if (subject != null) {
                            String subjectName = subjectMapper.selectNameById(course.getSubjectId());
                            dto.setSubjectName(subjectName);
                        }
                        
                        // 转换班型
                        Integer lessonType = course.getLessonType();
                        if (lessonType != null) {
                            switch (lessonType) {
                                case 1:
                                    dto.setLessonTypeName("大课");
                                    break;
                                case 2:
                                    dto.setLessonTypeName("小班课");
                                    break;
                                case 3:
                                    dto.setLessonTypeName("1v1");
                                    break;
                                default:
                                    dto.setLessonTypeName("未知");
                            }
                        }
                    }
                    
                    return dto;
                })
                .filter(dto -> {
                    // 过滤课程名称
                    if (condition.getLinkedCourseName() != null && !condition.getLinkedCourseName().isEmpty()) {
                        return dto.getName() != null && dto.getName().contains(condition.getLinkedCourseName());
                    }
                    return true;
                })
                .collect(Collectors.toList());
        
        // 构建分页结果
        PageDTO<CourseLinkDTO> result = new PageDTO<>();
        result.setPageIndex(page.getCurrent());
        result.setPageSize(page.getSize());
        result.setTotal((long) rows.size());
        result.setPages((long) Math.ceil((double) rows.size() / page.getSize()));
        result.setRows(rows);
        
        return result;
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Long saveCourseLink(Long courseId, List<Long> linkedCourseIds) {
        if (courseId == null) {
            throw new IllegalArgumentException("课程ID不能为空");
        }
        
        // 检查课程是否存在
        CourseDO course = courseMapper.selectById(courseId);
        if (course == null) {
            throw new IllegalArgumentException("课程不存在，ID: " + courseId);
        }
        
        // 添加新关联（避免重复添加）
        if (linkedCourseIds != null && !linkedCourseIds.isEmpty()) {
            for (Long linkedId : linkedCourseIds) {
                if (linkedId == null) {
                    continue; // 跳过空的关联课程ID
                }
                
                // 检查是否自己关联自己
                if (courseId.equals(linkedId)) {
                    throw new IllegalArgumentException("不允许课程自己关联自己，课程ID: " + courseId);
                }
                
                // 检查关联课程是否存在
                CourseDO linkedCourse = courseMapper.selectById(linkedId);
                if (linkedCourse == null) {
                    throw new IllegalArgumentException("关联课程不存在，ID: " + linkedId);
                }
                
                // 检查是否已存在关联
                LambdaQueryWrapper<CourseLinkDO> checkWrapper = new LambdaQueryWrapper<>();
                checkWrapper.eq(CourseLinkDO::getCourseId, courseId)
                        .eq(CourseLinkDO::getLinkedId, linkedId);
                CourseLinkDO existingLink = courseLinkMapper.selectOne(checkWrapper);
                
                // 如果已存在关联，抛出异常
                if (existingLink != null) {
                    throw new IllegalArgumentException("课程与关联课程已存在关联关系，课程ID: " + courseId + ", 关联课程ID: " + linkedId);
                }
                
                // 添加新关联
                CourseLinkDO link = new CourseLinkDO();
                link.setCourseId(courseId);
                link.setLinkedId(linkedId);
                courseLinkMapper.insert(link);
            }
        }
        
        return courseId;
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public List<Long> removeCourseLink(Long courseId, List<Long> linkedCourseIds) {
        if (courseId == null) {
            throw new IllegalArgumentException("课程ID不能为空");
        }
        
        if (linkedCourseIds == null || linkedCourseIds.isEmpty()) {
            return linkedCourseIds; // 空列表直接返回
        }
        
        // 检查课程是否存在
        CourseDO course = courseMapper.selectById(courseId);
        if (course == null) {
            throw new IllegalArgumentException("课程不存在，ID: " + courseId);
        }
        
        // 检查并删除关联
        List<Long> deletedIds = new ArrayList<>();
        
        for (Long linkedId : linkedCourseIds) {
            if (linkedId == null) {
                continue; // 跳过空的关联课程ID
            }
            
            // 检查是否自己关联自己（这种情况不可能存在）
            if (courseId.equals(linkedId)) {
                log.warn("不允许删除课程自己关联自己的记录，课程 ID: " + courseId);
                continue;
            }
            
            // 检查关联是否存在
            LambdaQueryWrapper<CourseLinkDO> checkWrapper = new LambdaQueryWrapper<>();
            checkWrapper.eq(CourseLinkDO::getCourseId, courseId)
                    .eq(CourseLinkDO::getLinkedId, linkedId);
            CourseLinkDO existingLink = courseLinkMapper.selectOne(checkWrapper);
            
            if (existingLink == null) {
                log.warn("关联课程记录不存在，课程 ID: " + courseId + ", 关联课程 ID: " + linkedId);
                continue;
            }
            
            // 执行删除
            courseLinkMapper.delete(checkWrapper);
            deletedIds.add(linkedId);
        }
        
        return deletedIds;
    }
}
